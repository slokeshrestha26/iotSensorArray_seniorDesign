/*This code implements the data parsing that happens in the wristband side after the data is sent from the wristband.*/

#include<stdio.h>
#include<stdlib.h>


#define DEBUG true // flag for serial feedback for debug
// these lengths are for a minute
#define DATA_ACC_LENGHT_PER_AXIS 1560 
#define DATA_HR_LENGTH 60

// Global Variables for data
double data_acc[DATA_ACC_LENGHT_PER_AXIS*3]; // Flattened data which is arranged as: [accx, accy, accz]
double data_hr[DATA_HR_LENGTH];
char ble_buff[4]; //character array for bluetooth buffer. QUESTION: HOW DO WE HANDLE NEGATIVE NUMBERS FOR ACC DATA


// index of the array to populate. Associated with:
//           - parse_data(double data[], char ble_buff[]) method. 
//           - reset_idx(int &accx, int &accy, int &accz, int &hr) method.
//           
// SUGGESTION: Would be good if class is implemented
int idx_accx = 0;
int idx_accy = DATA_ACC_LENGHT_PER_AXIS;
int idx_accz = DATA_ACC_LENGHT_PER_AXIS*2;
int idx_hr = 0;

//Fucntion Definition
int predict_trivial(double acc[], double hr[]);
double avg(double a[], int size);
double avg(int a[], int size);
double parse_data(char a[]);
void parse_data(double data[], char ble_buff[]);
void reset_idx(int &accx, int &accy, int &accz, int &hr);

void setup(){
    #if DEBUG
        Serial.begin(9600);
    #endif
}
void loop(){
    predict_trivial(acc, hr);

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


int main(){
    char strx[4] = {'x','5','0','4'};
    char stry[4] = {'y','4','1','0'};
    char strz[4] = {'z','3','1','2'};
    char strh[4] = {'h','3','3','3'};
    int x = parse_data(strx);
    printf("%d \n", x);

    return 0;
}

double parse_data(char a[]){
    /*Returns the character array that is parsed into doubles*/
    char b[] = {a[1], a[2], a[3], '\0'};
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

    case 'y':
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

void reset_idx(int &accx, int &accy, int &accz, int &hr){
    /* Resets the insert index for the data array*/

    accx = 0;
    accy = DATA_ACC_LENGHT_PER_AXIS;
    accz = DATA_ACC_LENGHT_PER_AXIS*2;
    hr = DATA_ACC_LENGHT_PER_AXIS*3;

}


void generate_data_trivial(){


}