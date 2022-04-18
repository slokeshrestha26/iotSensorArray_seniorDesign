#include <SoftwareSerial.h>
#define DATA_ACC_LENGHT_PER_AXIS 780 
#define DATA_HR_LENGTH 30
#define BLE_BUFF_SIZE 5

#define DEBUG false

SoftwareSerial hm10(7,8); //RX, TX 


// Global Variables for data
double data_acc[DATA_ACC_LENGHT_PER_AXIS*3]; // Flattened data which is arranged as: [accx, accy, accz]
double data_hr[DATA_HR_LENGTH];
char ble_buff[BLE_BUFF_SIZE]; //character array for bluetooth buffer. QUESTION: HOW DO WE HANDLE NEGATIVE NUMBERS FOR ACC DATA

//Function Definition
int predict_trivial();
double avg(double a[], int size);
double avg(int a[], int size);
int convert_to_int(char a[]);
void parse_data();
void reset_idx(int& accx, int& accy, int& accz, int& hr);
void populate_ble_buff();

/* index of the array to populate. Associated with:
          - parse_data(double data[], char ble_buff[]) method. 
          - reset_idx(int &accx, int &accy, int &accz, int &hr) method.
          
SUGGESTION: Would be good if class is implemented
*/
int idx_accx = 0;
int idx_accy = DATA_ACC_LENGHT_PER_AXIS;
int idx_accz = DATA_ACC_LENGHT_PER_AXIS*2;
int idx_hr = 0;

int stress = 0;

bool data_arr_has_space = true;

int counter_ble_buff = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  hm10.begin(115200);  
  hm10.write("AT+NOTIFY_ON0010");
}
 
void loop() {
  populate_ble_buff();

  data_arr_has_space = (idx_accx < DATA_ACC_LENGHT_PER_AXIS || idx_accy < DATA_ACC_LENGHT_PER_AXIS*2 || idx_accz < DATA_ACC_LENGHT_PER_AXIS*3);


  if(data_arr_has_space){ parse_data(); }
  else{
    stress = predict_trivial();
    reset_idx(idx_accx, idx_accy, idx_accz, idx_hr);
    counter_ble_buff = 0;
  }

  if(stress == 1){
    Serial.println(stress);
    hm10.write("At+SEND_DATAWN000E1");
    stress = 0;
  }

}


//===================== FUNCTIONS IMPLEMENTATION===================

void populate_ble_buff(){
  /*Populate ble buffer from hm10
  Only populate if the data is not rubbish. (data might be rubbish if wristband does not send data to waistband fast enough)
  */


  while(counter_ble_buff < 5){
    if (hm10.available()){
      
      byte data = hm10.read();
    
      if((int) data != 255){// if data is not rubbish,
        ble_buff[counter_ble_buff] = data;
        
        // only increment the counter if first element of the buffer is x, y, z, or h. Not incrementing the counter will ensure that ble_buff[0] will always have either x,y,z,or h.
        if((ble_buff[0] == (int)'h') || ble_buff[0] == (int)'x' || ble_buff[0] == (int)'y' || ble_buff[0] == (int)'z') {
          counter_ble_buff++;
          }//end if
          
      }//end if
      
     }//end if
   }

  counter_ble_buff = 0;
  
}//end populate_ble_buff()

int predict_trivial(){
    /*Implementing a trivial model for proof of concept*/
    double avg_acc = fabs(avg(data_acc, DATA_ACC_LENGHT_PER_AXIS*3));
    double avg_hr = avg(data_hr, DATA_HR_LENGTH);

    if (avg_acc > 30 || avg_hr > 20){
        #if DEBUG
          Serial.println("Stress Detected");
          delay(500);
        #endif
        return 1;
    }
    else{
      #if DEBUG
        Serial.println("No Stress Detected");
        delay(500);
      #endif
      return 0;
    }
}

double avg(double a[], int size){
    /*Function for calculating average for double array*/
    double accum = 0;
    for(int i = 0; i < size; i++){
        accum += a[i];
    }

    return accum/size;
}

double avg(int a[], int size){
    /*Function for calculating average for integrer array*/

    double accum = 0;
    for(int i = 0; i < size; i++){
        accum += a[i];
    }

    return accum/size;
}


int convert_to_int(char a[]){
    /*Returns the character array that is parsed into int
    */
    char b[] = {a[1], a[2], a[3], a[4],'\0'};
    return atoi(b);
}

void parse_data(){
    /*  Parses data and inserts the double data into suitable indexes in the array. 
    data[]: A minute worth of data that needs to be passed to a model
    ble_buff[]: Array of four character arrays. 
    */

    char type = (char)ble_buff[0];
    
    switch (type)
    {
    case 'x':
        data_acc[idx_accx] = convert_to_int(ble_buff);
        idx_accx++;
        break;

    case 'y':
        data_acc[idx_accy] = convert_to_int(ble_buff);
        idx_accy++;
        break;

    case 'z':
        data_acc[idx_accz] = convert_to_int(ble_buff);
        idx_accz++;
        break;

    case 'h':
        data_hr[idx_hr] = convert_to_int(ble_buff);
        idx_hr++;
        break;

    default:
        break;
    }

}

void reset_idx(int& accx, int& accy, int& accz, int& hr){
    /* Resets the insert index for the data array*/
    accx = 0;
    accy = DATA_ACC_LENGHT_PER_AXIS;
    accz = DATA_ACC_LENGHT_PER_AXIS*2;
    hr = DATA_ACC_LENGHT_PER_AXIS*3;

}