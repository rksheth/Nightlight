/* ############################################
   Nightlight functionality on the Raspberry Pi
   Written by Rushi for shits and giggles
   ############################################ */



#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>

/* #############################################
   Some #defined Globals
   #############################################*/
#define PWM_PIN           18
#define PWM_MAX_VALUE     1024

#define I2C_SENSOR_DEVICE_ADDRESS 0x39

#define I2C_SENSOR_CTRL_REG_ADDR 0x00
#define I2C_SENSOR_ID_REG_ADDR 0x0A
#define I2C_SENSOR_CMD_REG_ADDR
#define I2C_SENSOR_CMD_REG_WRITE
#define I2C_SENSOR_SELECT_CH0_LOW_REG (0x1<<7) & (0xC << 0)
#define I2C_SENSOR_SELECT_CH0_HIGH_REG (0x1<<7) & (0xD << 0)
#define I2C_SENSOR_SELECT_CH1_LOW_REG (0x1<<7) & (0xE << 0)
#define I2C_SENSOR_SELECT_CH1_HIGH_REG (0x1<<7) & (0xF << 0)
#define I2C_SENSOR_SELECT_CTRL_REG (0x1<<7) & (0x0 << 0)
#define I2C_SENSOR_CH0_LOW_REG_ADDR
#define I2C_SENSOR_CH0_HIGH_REG_ADDR
#define I2C_SENSOR_CH1_LOW_REG_ADDR
#define I2C_SENSOR_CH1_HIGH_REG_ADDR


/* #############################################
   Some Function Prototypes
   #############################################*/

void powerUpSensor(int fd);
void powerDownSensor(int fd);
void readRawData(int fd, unsigned short int * rawVisible, unsigned short int * rawInfra);
void printSensorId(int fd);


/* #############################################
   Main processing function
   #############################################*/

int main(int argc, char * argv[]){
	

    int i, fd;
    unsigned short int rawVisible, rawInfra;
    fd = wiringPiI2CSetup(I2C_SENSOR_DEVICE_ADDRESS);
    if(fd < 0){
        printf("Error opening I2C device! Error %x.\n", fd);
        return fd;
    }
    printf("Opened Device at I2C address %x. File handle %d. \n", I2C_SENSOR_DEVICE_ADDRESS, fd);

    powerUpSensor(fd);
    /*Light Sensor data is ready 400 ms after power on*/
    delay(403);
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
    
    powerDownSensor(fd);
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


void powerUpSensor(int fd){
    
    int payload, output;

    /*Write command register - access CTRL reg*/
    wiringPiI2CWrite(fd, I2C_SENSOR_SELECT_CTRL_REG);

    /*Turn on the Device*/
    /*WRITE the value 0x03 to CTRL reg*/
    payload= 0x03;
    wiringPiI2CWrite(fd, payload);

    /*check that we powered on correctly*/
    output = wiringPiI2CRead(fd);
    if((output & 0x3) == payload)
    {
        printf("Light Sensor Power on Successful! CMD REG: %x\n", output);
    }
    else
    {
        printf("Light Sensor Power on Failed!\n");
        printf("CTRL reg value = 0x%x.\n", output);
    }

}

void powerDownSensor(int fd){
    /*WRITE the value 0x00 to CTRL reg*/
    int payload, output;
    
    /*Configure CTRL register for write*/ 
    wiringPiI2CWrite(fd, I2C_SENSOR_SELECT_CTRL_REG);
    
    payload= 0x00;
    wiringPiI2CWrite(fd, payload);

    /*Not sure if supported for power off*/
    /*check that we powered on correctly*/
    output = wiringPiI2CRead(fd);
    if((output & 0x3) == payload)
    {
        printf("Light Sensor Power on Successful! CMD REG: %x\n", output);
    }
    else
    {
        printf("Light Sensor Power off Failed!\n");
        printf("CTRL reg value = %d.\n", output);
    }
}


void readRawData(int fd, unsigned short int * rawVisible, unsigned short int * rawInfra){
    
    /*Do this as a struct & memset*/
    char temp;
    *rawVisible = 0;
    *rawInfra = 0;

    wiringPiI2CWrite(fd, I2C_SENSOR_SELECT_CH0_LOW_REG);
    temp = wiringPiI2CRead(fd);
    printf("CH0 Low: %x\n", (int)temp);

    wiringPiI2CWrite(fd, I2C_SENSOR_SELECT_CH0_HIGH_REG);
    temp = wiringPiI2CRead(fd);
    printf("CH0 High: %x\n", (int)temp);

    wiringPiI2CWrite(fd, I2C_SENSOR_SELECT_CH1_LOW_REG);
    temp = wiringPiI2CRead(fd);
    printf("CH1 Low: %x\n", (int)temp);

    wiringPiI2CWrite(fd, I2C_SENSOR_SELECT_CH1_HIGH_REG);
    temp= wiringPiI2CRead(fd);
    printf("CH1 High: %x\n", (int)temp);
/*
//Read the lower 8 bits
//Write to DeviceConfigure command register - read mode & register to read
//Read the upper 8 bits
//lower << 8 & upper = 16-bit digital light sensor value
//repeat for infrared light.
*/
}




void printSensorId(int fd){

    int output;
    wiringPiI2CWrite(fd, I2C_SENSOR_ID_REG_ADDR);

    output = wiringPiI2CRead(fd);
    printf("Light Sensor ID: %x\n", output);

}





