/* ############################################
   Nightlight functionality on the Raspberry Pi
   Written by Rushi for shits and giggles
   ############################################ */

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <inttypes.h>
#include "i2c.h"

/* #############################################
   Main processing function
   #############################################*/

int main(int argc, char * argv[]){
	

    int i, fd;
    uint16_t data;
    unsigned short int rawVisible, rawInfra;
    fd = wiringPiI2CSetup(TSL2561_DEVICE_ADDRESS);
    if(fd < 0){
        printf("Error opening I2C device! Error %x.\n", fd);
        return fd;
    }
    printf("Opened Device at I2C address %x. File handle %d. \n", TSL2561_DEVICE_ADDRESS, fd);

    TSL2561_POWERON(fd);

    /*Static inline function for clarity*/
    wiringPiSetupGpio();
    pinMode(PWM_PIN, PWM_OUTPUT);

   /* printSensorId(fd);*/
    TSL2561_AUTOGAIN(fd);   
    printf("Reading frm Ch0 Low Reg: 0x%x", TSL2561_SELECT_CH0_LOW_REG);

    /*make this a while(1) loop, handle user exiting*/
    for(i = 0; i < 10000; i++){

        /*Light Sensor data is ready 400 ms after power on*/
        delay(500);

        /*read data out from sensor*/
        readRawData(fd, &rawVisible, &rawInfra);

        /*just print values to the screen for now*/
        printf("Visible: 0x%x. Infra: 0x%x. \n", rawVisible, rawInfra);
    }
    
    TSL2561_POWEROFF(fd);
    return 0;



 /*


	}
*/	


}

void adjustNightlight(unsigned short int * rawVisible){
    int quantLevel;

    /*scale this somehow*/
    quantLevel = *rawVisible;
    pwmWrite(PWM_PIN, quantLevel);
}

void readRawData(int fd, unsigned short int * rawVisible, unsigned short int * rawInfra){
    
    /*Channel 0 has both Infrared & Visible Light*/
    *rawVisible = wiringPiI2CReadReg16(fd, TSL2561_SELECT_CH0_LOW_REG);
    /*Channel 1 has just Infrared Light*/
    *rawInfra = wiringPiI2CReadReg16(fd, TSL2561_SELECT_CH1_LOW_REG);
    return;
}




void printSensorId(int fd){

    int output;
/*
    wiringPiI2CWrite(fd, TSL2561_ID_REG_ADDR);
    output = wiringPiI2CRead(fd);
*/
    output = wiringPiI2CReadReg8(fd, TSL2561_ID_REG_ADDR);
    printf("Light Sensor ID: %x\n", output);


}

