/* #############################################
   Some #defined Globals
   #############################################*/
#define PWM_PIN           18
#define PWM_MAX_VALUE     1024

#define TSL2561_DEVICE_ADDRESS 0x39

#define TSL2561_CTRL_REG_ADDR 0x00
#define TSL2561_CTRL_PAYLOAD_ON 0x03
#define TSL2561_CTRL_PAYLOAD_OFF 0x00
#define TSL2561_ID_REG_ADDR   0x0A
#define TSL2561_CMD_REG_ADDR
#define TSL2561_CMD_REG_WRITE

#define TSL2561_CMD_BIT (0x1 << 7)

#define TSL2561_SELECT_ID_REG (0x1<<7) | (0x0A < 0)
#define TSL2561_SELECT_CH0_LOW_REG (0x1<<7) | (0xC << 0)
#define TSL2561_SELECT_CH0_HIGH_REG (0x1<<7)|  (0xD << 0)
#define TSL2561_SELECT_CH1_LOW_REG (0x1<<7) | (0xE << 0)
#define TSL2561_SELECT_CH1_HIGH_REG (0x1<<7) | (0xF << 0)
#define TSL2561_SELECT_CTRL_REG (0x1<<7) | (0x0 << 0)

#define TSL2561_GAIN_AUTO                (0x01)
#define TSL2561_REGISTER_TIMING            (0x81)


/*
#define TSL2561_SELECT_ID_REG 0x0A
#define TSL2561_SELECT_CH0_LOW_REG 0xC
#define TSL2561_SELECT_CH0_HIGH_REG 0xD
#define TSL2561_SELECT_CH1_LOW_REG 0xE
#define TSL2561_SELECT_CH1_HIGH_REG 0xF
#define TSL2561_SELECT_CTRL_REG 0x0
*/

#define TSL2561_CH0_LOW_REG_ADDR
#define TSL2561_CH0_HIGH_REG_ADDR
#define TSL2561_CH1_LOW_REG_ADDR
#define TSL2561_CH1_HIGH_REG_ADDR


/* #############################################
   Some Function Prototypes
   #############################################*/

void readRawData(int fd, unsigned short int * rawVisible, unsigned short int * rawInfra);
void printSensorId(int fd);
