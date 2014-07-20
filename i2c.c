/* ############################################
   Nightlight functionality on the Raspberry Pi
   Written by Rushi for shits and giggles
   ############################################ */

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include "i2c.h"



/*
* Some Function Macros to clean things up
*/

#define TSL2561_POWERON(int fd) wiringPiI2CWriteReg8(fd, TSL2561_COMMAND_BIT, TSL2561_CONTROL_POWERON)
#define TSL2561_POWEROFF(int fd) wiringPiI2CWriteReg8(fd, TSL2561_COMMAND_BIT, TSL2561_CONTROL_POWEROFF)

/* #############################################
   Main processing function
   #############################################*/

int main(int argc, char * argv[]){
	

    int i, fd;
    unsigned short int rawVisible, rawInfra;
    fd = wiringPiI2CSetup(TSL2561_DEVICE_ADDRESS);
    if(fd < 0){
        printf("Error opening I2C device! Error %x.\n", fd);
        return fd;
    }
    printf("Opened Device at I2C address %x. File handle %d. \n", TSL2561_DEVICE_ADDRESS, fd);

    TSL2561_POWERON(fd);
    /*Light Sensor data is ready 400 ms after power on*/
    printSensorId(fd);
    /*make this a while(1) loop*/
    for(i = 0; i < 10; i++){
        /*(while loop) user can type 'exit' to quit*/
        delay(403);
        /*read data out from sensor*/
       readRawData(fd, &rawVisible, &rawInfra);
        /*just print values to the screen for now*/
        printf("Visible: 0x%x. Infra: 0x%x. \n", rawVisible, rawInfra);
    }
    
    TSL2561_POWEROFF(fd);
    return 0;



 /*
    int i;
	wiringPiSetupGpio();
    pinMode(PWM_PIN, PWM_OUTPUT);

	while(1){
		for(i = 0; i < PWM_MAX_VALUE; i++){
			pwmWrite(PWM_PIN, i);
			delay(5);
		}
		
		for(; i > 0; i--){
			pwmWrite(PWM_PIN, i);
			delay(5);
		}

	}
*/	


}

void readRawData(int fd, unsigned short int * rawVisible, unsigned short int * rawInfra){
    
    /*conver to 16 bit read?*/
    /*do we have to write the timing register?*/
    /*Do this as a struct & memset*/
    char reading[2];
    *reading = wiringPiI2CReadReg16(fd, TSL2561_REGISTER_CHAN0_LOW);
    *rawVisible = reading[0];
    *rawInfra = reading[1];
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

