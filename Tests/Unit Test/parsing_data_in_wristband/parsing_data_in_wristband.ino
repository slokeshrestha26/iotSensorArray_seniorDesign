/*This code implements the data parsing that happens in the wristband side after the data is sent from the wristband.*/

#include<stdio.h>
#include<stdlib.h>

#define TEST true
#define DEBUG true // flag for serial feedback for debug
// these lengths are for a minute
#define DATA_ACC_LENGHT_PER_AXIS 1560 
#define DATA_HR_LENGTH 60

// Global Variables for data
double data_acc[DATA_ACC_LENGHT_PER_AXIS*3]; // Flattened data which is arranged as: [accx, accy, accz]
double data_hr[DATA_HR_LENGTH];
char ble_buff[5]; //character array for bluetooth buffer. QUESTION: HOW DO WE HANDLE NEGATIVE NUMBERS FOR ACC DATA
void generate_data_trivial(char ble_buff[], int counter);


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

//Fucntion Definition
int predict_trivial(double acc[], double hr[]);
double avg(double a[], int size);
double avg(int a[], int size);
double parse_data(char a[]);
void parse_data(double data[], char ble_buff[]);
void reset_idx(int& accx, int& accy, int& accz, int& hr);
void generate_data_trivial(char ble_buff[], int counter);

void setup(){
    #if DEBUG
        Serial.begin(9600);
    #endif
}
void loop(){
    //test indexes
    int data_acc_test_idx[] = {1557, 1558, 1559, 3117, 3118, 3119, 4677, 4678, 4679};
    int data_hr_test_idx[] = {57, 58,59};

    generate_data_trivial(ble_buff, loop_counter); //populates the character array

    bool data_arr_is_empty = (idx_accx < DATA_ACC_LENGHT_PER_AXIS || idx_accy < DATA_ACC_LENGHT_PER_AXIS*2 || idx_accz < DATA_ACC_LENGHT_PER_AXIS*3 || idx_hr < DATA_HR_LENGTH);
    if (data_arr_is_empty){
        if(ble_buff[0] != 'h'){
            parse_data(data_acc, ble_buff);
        }
        else{
            parse_data(data_hr, ble_buff);
        }
        loop_counter++;
    }
    
    if(!data_arr_is_empty){ //if data array is populated, run the model, reset data indexes and loop counter
        predict_trivial(data_acc, data_hr);

        #if TEST
            Serial.println("=======Test 1: DATA POPULAION TEST=========");
            // ACC test
            Serial.print("Contents of data_acc at indexes: [1557, 1558, 1559, 3117, 3118, 3119, 4677, 4678, 4679] are: ");
            for(int i = 0; i < 3*3; i++){
                Serial.print(data_acc[data_acc_test_idx[i]]);
                Serial.print(",");
            }
            Serial.println("\n");
            // HR test
            Serial.print("The content of data_hr at index [57, 58,59]: ");
            for(int i = 0; i < 3; i++){
                Serial.print(data_hr[data_hr_test_idx[i]]);
                Serial.print(",");
            }

            Serial.println("\n\n");
        #endif

        #if TEST
            Serial.println("=======Test 2: INDEX RESET TEST=========");
            Serial.println("Before reset_idx is called: ");
            Serial.print("idx_accx: ");
            Serial.println(idx_accx);
            Serial.print("idx_accy: ");
            Serial.println(idx_accy);
            Serial.print("idx_accz: ");
            Serial.println(idx_accz);
            Serial.print("idx_hr: ");
        Serial.println(idx_hr);
        #endif

        reset_idx(idx_accx, idx_accy, idx_accz, idx_hr);
        #if TEST
            Serial.println("After reset_idx is called: ");
            Serial.print("idx_accx: ");
            Serial.println(idx_accx);
            Serial.print("idx_accy: ");
            Serial.println(idx_accy);
            Serial.print("idx_accz: ");
            Serial.println(idx_accz);
            Serial.print("idx_hr: ");
        Serial.println(idx_hr);
        #endif
        delay(30000);
        loop_counter = 0;
    }
}

int predict_trivial(double acc[], double hr[]){
    /*Implementing a trivial model for proof of concept*/
    
    if (avg(acc, DATA_ACC_LENGHT_PER_AXIS*3) > 50 || avg(hr, DATA_HR_LENGTH) > 50){
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


void generate_data_trivial(char ble_buff[], int counter){
    /*Trivial subroutine to simulate data generation to get around bluetooth. 
    counter will define which data (among accx,accy,accz,hr) to send*/

    switch (counter % 4)
    {
    case 0:
        ble_buff[0] = 'x';
        ble_buff[1] = '-';
        ble_buff[2] = '5';
        ble_buff[3] = '0';
        ble_buff[4] = '4';
        break;
    case 1:
        ble_buff[0] = 'y';
        ble_buff[1] = '0';
        ble_buff[2] = '5';
        ble_buff[3] = '0';
        ble_buff[4] = '4';
        break;
    case 2:
        ble_buff[0] = 'z';
        ble_buff[1] = '-';
        ble_buff[2] = '5';
        ble_buff[3] = '0';
        ble_buff[4] = '4';
        break;
    case 3:
        ble_buff[0] = 'h';
        ble_buff[1] = '0';
        ble_buff[2] = '5';
        ble_buff[3] = '0';
        ble_buff[4] = '4';
        break;
    default:
        break;
    }
}
