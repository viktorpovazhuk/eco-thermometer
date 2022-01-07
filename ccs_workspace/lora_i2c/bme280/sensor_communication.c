#include <bme280/sensor_communication.h>


/* CMD_TYPE_X_SLAVE are example commands the master sends to the slave.
 * The slave will send example SlaveTypeX buffers in response.
 *
 * CMD_TYPE_X_MASTER are example commands the master sends to the slave.
 * The slave will initialize itself to receive MasterTypeX example buffers.
 * */

#define CMD_TYPE_0_SLAVE      0
#define CMD_TYPE_1_SLAVE      1
#define CMD_TYPE_2_SLAVE      2

#define CMD_TYPE_0_MASTER      3
#define CMD_TYPE_1_MASTER      4
#define CMD_TYPE_2_MASTER      5

#define TMP117_LENGTH    2
#define OPT3001_LENGTH   2
#define HDC2080_LENGTH   1

extern uint8_t Opt3001SlaveBuffer[OPT3001_LENGTH] = {0};
extern uint8_t TMP117SlaveBuffer[TMP117_LENGTH] = {0};
extern uint8_t HDC2080SlaveBuffer[HDC2080_LENGTH] = {0};

//******************************************************************************
// Use to get the Opt3001 Lux data *********************************************
//******************************************************************************
uint16_t caculateQuadraticValue(char number)
{
    uint8_t count;
    uint16_t returnValue =1;
    for(count=0; count<number; count++)
    {
        returnValue = returnValue*2;
    }
    return returnValue;
}

void opt3001Init()
{
    Opt3001SlaveBuffer[0] =0xCE; //Make OPT3001 works under continues mode
    Opt3001SlaveBuffer[1] =0x01;
    I2C_Master_WriteReg(OPT3001_SLAVE_ADDR, 0x01, Opt3001SlaveBuffer, OPT3001_LENGTH);
}
uint16_t getOpt3001LuxData(void)
{
    uint16_t luxData;
    I2C_Master_ReadReg(OPT3001_SLAVE_ADDR, 0x00, OPT3001_LENGTH);//read to result register
    CopyArray(ReceiveBuffer, Opt3001SlaveBuffer, OPT3001_LENGTH);
    luxData = ((caculateQuadraticValue(Opt3001SlaveBuffer[0]>>4))*((Opt3001SlaveBuffer[0]<<8) + Opt3001SlaveBuffer[1]));
    return luxData;
}
//******************************************************************************
// Use to get the Opt3001 Lux data *********************************************
//******************************************************************************
int8_t getTmp117TemperatureData(void)
{
    uint16_t tempData;
    I2C_Master_ReadReg(TMP117_SLAVE_ADDR, 0x00, TMP117_LENGTH);//read to result register
    CopyArray(ReceiveBuffer, TMP117SlaveBuffer, TMP117_LENGTH);
    tempData = (TMP117SlaveBuffer[0]<<8)+ TMP117SlaveBuffer[1];

    if(tempData<0x8000) //temp>0 C
    {
        return (tempData/(0x7FFF>>8));
    }
    else
    {
        return -((0xFFFF-tempData)/(0x7FFF>>8));
    }
}

//******************************************************************************
// Use to get the Humidity data *********************************************
//******************************************************************************
uint8_t getHdc2080HumidityData(void)
{
    uint32_t humidityData;
    HDC2080SlaveBuffer[0] =0x01;
    I2C_Master_WriteReg(HDC2080_SLAVE_ADDR, 0x0F, HDC2080SlaveBuffer,HDC2080_LENGTH);//Write to result register
    __delay_cycles(16000); //1ms
    __delay_cycles(16000); //1ms
    __delay_cycles(16000); //1ms
    I2C_Master_ReadReg(HDC2080_SLAVE_ADDR, 0x02, HDC2080_LENGTH);//Read result register
    CopyArray(ReceiveBuffer, HDC2080SlaveBuffer, HDC2080_LENGTH);
    humidityData = HDC2080SlaveBuffer[0];
    I2C_Master_ReadReg(HDC2080_SLAVE_ADDR, 0x03, HDC2080_LENGTH);//Read result register
    CopyArray(ReceiveBuffer, HDC2080SlaveBuffer, HDC2080_LENGTH);
    humidityData += (HDC2080SlaveBuffer[0]<<8);
    return ((humidityData *100)>>16);
}

void hdc2080Init()
{

}
