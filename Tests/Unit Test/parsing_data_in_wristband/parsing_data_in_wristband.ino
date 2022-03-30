/*This code implements the data parsing that happens in the wristband side after the data is sent from the wristband.*/

#include<stdio.h>
#include<stdlib.h>

#ifndef MyClass_h
#define MyClass_h
#include "Arduino.h"

#define DEBUG true
// these lengths are for a minute
#define DATA_ACC_LENGHT_PER_AXIS 1560 
#define DATA_HR_LENGTH 60

// Global Variables

double acc[DATA_ACC_LENGHT_PER_AXIS*3];
double hr[DATA_HR_LENGTH];

//Fucntion Definition
int predict_trivial(double acc[], double hr[]);
double avg(double a[], int size);
double avg(int a[], int size);
double parse_data(char a[]);



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

double parse_data(char accx[], char accy[], char accz[], char hr[]){
    /*Assigns the data to */
}