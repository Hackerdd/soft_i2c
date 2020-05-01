/***
	File name           :soft_i2c.c
	file identification :
	Subject             :Say something about the file

	Current Version     :V1.0.0
	Author              :Hacker
	Date                :

	Instead Version     :
	Author              :Hacker
	Date                :
***/
#include "soft_i2c.h"


//产生I2C起始信号
void I2C_Start(void)
{
	SET_SDA_OUT();     //sda线输出
	I2C_SDA_1();	  	  
	I2C_SCL_1();
	NOP(4);
 	I2C_SDA_0();//START:when CLK is high,DATA change form high to low 
	NOP(4);
	I2C_SCL_0();//钳住I2C总线，准备发送或接收数据 
}

//产生I2C停止信号
void I2C_Stop(void)
{
	SET_SDA_OUT();//sda线输出
	I2C_SCL_0();
	I2C_SDA_0();//STOP:when CLK is high DATA change form low to high
 	NOP(4);
	I2C_SCL_1(); 
	I2C_SDA_1();//发送I2C总线结束信号
	NOP(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t I2C_Wait_Ack(void)
{
	uint16_t ucErrTime = 0;
	SET_SDA_IN();      //SDA设置为输入  
	I2C_SDA_1();NOP(1);	   
	I2C_SCL_1();NOP(1);	 
	while(I2C_SDA_READ())
	{
		ucErrTime ++;
		if(ucErrTime > 250)
		{
			I2C_Stop();
			return 1;
		}
	}
	I2C_SCL_0();//时钟输出0 	   
	return 0;  
}

//产生ACK应答
void I2C_Ack(void)
{
	I2C_SCL_0();
	SET_SDA_OUT();
	I2C_SDA_0();
	NOP(2);
	I2C_SCL_1();
	NOP(2);
	I2C_SCL_0();
}

//不产生ACK应答		    
void I2C_NAck(void)
{
	I2C_SCL_0();
	SET_SDA_OUT();
	I2C_SDA_1();
	NOP(2);
	I2C_SCL_1();
	NOP(2);
	I2C_SCL_0();
}

//I2C发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void I2C_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	SET_SDA_OUT(); 	    
    I2C_SCL_0();//拉低时钟开始数据传输
    for(t = 0;t < 8;t ++)
    {              
		if((txd&0x80) >> 7)
			I2C_SDA_1();
		else
			I2C_SDA_0();
		txd <<= 1; 	  
		NOP(2);   
		I2C_SCL_1();
		NOP(2); 
		I2C_SCL_0();	
		NOP(2);
    }	 
}


//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t I2C_Rece_Byte(unsigned char ack)
{
	unsigned char i,receive = 0;
	SET_SDA_IN();//SDA设置为输入
    for(i = 0;i < 8;i ++)
	{
        I2C_SCL_0(); 
        NOP(2);
		I2C_SCL_1();
        receive <<= 1;
        if(I2C_SDA_READ())
        	receive++;   
		NOP(1); 
    }					 
    if (!ack)
        I2C_NAck();//发送nACK
    else
        I2C_Ack(); //发送ACK

    SET_SDA_OUT(); 	    
	I2C_SDA_1();
   
    return receive;
}

/***
	send one frame by iic
***/
void i2cAction(uint8_t deviceAddr, uint8_t regAddress)
{
	I2C_Start();
	I2C_Send_Byte(deviceAddr<<1);
	I2C_Wait_Ack();
	I2C_Send_Byte(regAddress);
	I2C_Wait_Ack();
	I2C_Stop();
}

uint8_t  I2C_Write_Byte(uint8_t deviceAddr, uint8_t regAddress, uint8_t content)
{
	uint8_t err = 0;
	I2C_Start();
	I2C_Send_Byte(deviceAddr<<1);
    err = I2C_Wait_Ack();

	I2C_Send_Byte(regAddress);
    err = I2C_Wait_Ack();

	I2C_Send_Byte(content);
	err = I2C_Wait_Ack();
	I2C_Stop();	
	return err;
}

uint8_t  I2C_Read_Byte(uint8_t deviceAddr, uint8_t regAddress, uint8_t *content)
{
	uint8_t err = 0;
    I2C_Start();
    I2C_Send_Byte(deviceAddr<<1);
    err = I2C_Wait_Ack();

    I2C_Send_Byte(regAddress);
    err = I2C_Wait_Ack();

    I2C_Start();
    I2C_Send_Byte((deviceAddr<<1)|0x01);
    err = I2C_Wait_Ack();

    *content = I2C_Rece_Byte(0);//data read error
    I2C_Stop();
    return err;
}

/**
 * @brief [write blocks]
 * @details [long description]
 * 
 * @param deviceAddr [description]
 * @param regAddress [description]
 * @param content [description]
 * @param size [num of bytes]
 * @return [0->ok,1->error]
 */
uint8_t  I2C_Write_Bytes(uint8_t deviceAddr, uint8_t regAddress, const uint8_t *content, uint16_t size)
{
	uint8_t err = 0;
	I2C_Start();
	I2C_Send_Byte(deviceAddr<<1);
    err = I2C_Wait_Ack();

	I2C_Send_Byte(regAddress);
    err = I2C_Wait_Ack();

    for (int i = 0; i < size; ++i)
    {
		I2C_Send_Byte(*(content+i));
		err = I2C_Wait_Ack();	
    }

	I2C_Stop();	
	return err;
}

/**
 * @brief read blocks 
 * @details [long description]
 * 
 * @param deviceAddr [description]
 * @param regAddress [description]
 * @param content [description]
 * @param size [num of bytes]
 * @return [0->ok,1->error]
 */
uint8_t  I2C_Read_Bytes(uint8_t deviceAddr, uint8_t regAddress, uint8_t *content, uint16_t size)
{
	uint8_t err = 0;
    I2C_Start();
    I2C_Send_Byte(deviceAddr<<1);
    err = I2C_Wait_Ack();

    I2C_Send_Byte((regAddress<<1) | 0x01);

    for (int i = 0; i < size; ++i)
    {
	    err = I2C_Wait_Ack();
    	*(content + i) = I2C_Rece_Byte(1);//data read error
    }

    I2C_Stop();
    return err;
}


