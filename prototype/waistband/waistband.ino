#include <SoftwareSerial.h>
#define DATA_ACC_LENGHT_PER_AXIS 1560 
#define DATA_HR_LENGTH 60
#define BLE_BUFF_SIZE 5

#define DEBUG false

SoftwareSerial hm10(7,8); //RX, TX 


// Global Variables for data
double data_acc[DATA_ACC_LENGHT_PER_AXIS*3]; // Flattened data which is arranged as: [accx, accy, accz]
double data_hr[DATA_HR_LENGTH];
char ble_buff[BLE_BUFF_SIZE]; //character array for bluetooth buffer. QUESTION: HOW DO WE HANDLE NEGATIVE NUMBERS FOR ACC DATA

//Function Definition
int predict_trivial(double acc[], double hr[]);
double avg(double a[], int size);
double avg(int a[], int size);
double parse_data(char a[]);
void parse_data(double data[], char ble_buff[]);
void reset_idx(int& accx, int& accy, int& accz, int& hr);
void populate_ble_buff(char ble_buff[]);

// index of the array to populate. Associated with:
//           - parse_data(double data[], char ble_buff[]) method. 
//           - reset_idx(int &accx, int &accy, int &accz, int &hr) method.
//           
// SUGGESTION: Would be good if class is implemented
int idx_accx = 0;
int idx_accy = DATA_ACC_LENGHT_PER_AXIS;
int idx_accz = DATA_ACC_LENGHT_PER_AXIS*2;
int idx_hr = 0;

int loop_counter = 0; // counter to artificially fill up the data buffer.

 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  hm10.begin(115200);  
  delay(100);
  hm10.write("AT+NOTIFY_ON0010");
  delay(100);
}
 
void loop() {
  //check if data available from wristband
  bool data_arr_is_empty = true;
  
  while(data_arr_is_empty){
	  populate_ble_buff(ble_buff);
	  
	  data_arr_is_empty = (idx_accx < DATA_ACC_LENGHT_PER_AXIS || idx_accy < DATA_ACC_LENGHT_PER_AXIS*2 || idx_accz < DATA_ACC_LENGHT_PER_AXIS*3 || idx_hr < DATA_HR_LENGTH);
	  if (data_arr_is_empty){ //parse data if data array is empty
		  if(ble_buff[0] != 'h'){
			  parse_data(data_acc, ble_buff);
		  }
		  else{
			  parse_data(data_hr, ble_buff);
			  reset_idx(idx_accx, idx_accy, idx_accz, idx_hr);
		  }
	  }
  }

  else{
    stress = predict_trivial(data_acc, data_hr);
  }

  if(stress){
    hm10.write("At+SEND_DATAWN000E1");
    stress = 0;
  }

  //test, use code above for final implementation
  while(Serial.available()){
    byte data=Serial.read();
    hm10.write(data);
  }

}


//===================== FUNCTIONS IMPLEMENTATION===================

void populate_ble_buff(char ble_buff[]){
    /*Populated ble buffer from hm10*/

  if(hm10.available()){
    for (int i=0; i < BLE_BUFF_SIZE; i++){
      ble_buff[i] = hm10.read();
    }
  }
}

int predict_trivial(double acc[], double hr[]){
    /*Implementing a trivial model for proof of concept*/
    double avg_acc = avg(acc, DATA_ACC_LENGHT_PER_AXIS*3);
    double avg_hr = avg(hr, DATA_HR_LENGTH);

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


double parse_data(char a[]){
    /*Returns the character array that is parsed into doubles*/
    char b[] = {a[1], a[2], a[3], a[4],'\0'};
    return (double) atoi(b);
}

void parse_data(double data[], char ble_buff[]){
    /*  Parses data and inserts the double data into suitable indexes in the array. 
    data[]: A minute worth of data that needs to be passed to a model
    ble_buff[]: Array of four character arrays. 
    */

    char type = ble_buff[0];
    
    switch (type)
    {
    case 'x':
        data[idx_accx] = parse_data(ble_buff);
        idx_accx++;
        break;

    case 'y':
        data[idx_accy] = parse_data(ble_buff);
        idx_accy++;
        break;

    case 'z':
        data[idx_accz] = parse_data(ble_buff);
        idx_accz++;
        break;

    case 'h':
        data[idx_hr] = parse_data(ble_buff);
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
