/* #############################################
   Some #defined Globals
   #############################################*/
#define PWM_PIN           18
#define PWM_MAX_VALUE     1024

#define I2C_SENSOR_DEVICE_ADDRESS 0x39

#define I2C_SENSOR_CTRL_REG_ADDR 0x00
#define I2C_SENSOR_ID_REG_ADDR   0x0A
#define I2C_SENSOR_CMD_REG_ADDR
#define I2C_SENSOR_CMD_REG_WRITE

#define I2C_SENSOR_CMD_BIT (0x1 << 7)

#define I2C_SENSOR_SELECT_ID_REG (0x1<<7) & (0x0A < 0)
#define I2C_SENSOR_SELECT_CH0_LOW_REG (0x1<<7) & (0xC << 0)
#define I2C_SENSOR_SELECT_CH0_HIGH_REG (0x1<<7) & (0xD << 0)
#define I2C_SENSOR_SELECT_CH1_LOW_REG (0x1<<7) & (0xE << 0)
#define I2C_SENSOR_SELECT_CH1_HIGH_REG (0x1<<7) & (0xF << 0)
#define I2C_SENSOR_SELECT_CTRL_REG (0x1<<7) & (0x0 << 0)

/*
#define I2C_SENSOR_SELECT_ID_REG 0x0A
#define I2C_SENSOR_SELECT_CH0_LOW_REG 0xC
#define I2C_SENSOR_SELECT_CH0_HIGH_REG 0xD
#define I2C_SENSOR_SELECT_CH1_LOW_REG 0xE
#define I2C_SENSOR_SELECT_CH1_HIGH_REG 0xF
#define I2C_SENSOR_SELECT_CTRL_REG 0x0
*/

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