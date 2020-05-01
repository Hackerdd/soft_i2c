/***
    File name           :soft_i2c.h
    file identification :
    Subject             :

    Current Version     :V1.0.0
    Author              :Hacker
    Date                :

    Instead Version     :
    Author              :Hacker
    Date                :
***/

#ifndef __SOFT_I2C__
#define __SOFT_I2C__

#include "main.h"
 
#define GPIO_PORT_I2C   GPIOA                // GPIO端口 
#define I2C_SCL_PIN     SCL_Pin          // 连接到SCL时钟线的GPIO 
#define I2C_SDA_PIN     SDA_Pin          // 连接到SDA数据线的GPIO 
 
#define SET_SDA_IN()    LL_GPIO_SetPinMode(GPIO_PORT_I2C, I2C_SDA_PIN, LL_GPIO_MODE_INPUT)
#define SET_SDA_OUT()   LL_GPIO_SetPinMode(GPIO_PORT_I2C, I2C_SDA_PIN, LL_GPIO_MODE_OUTPUT)
 
/* 定义读写SCL和SDA的宏 */
// #define I2C_SCL_1()  GPIO_PORT_I2C->BSRR = I2C_SCL_PIN                                          // SCL = 1 
// #define I2C_SCL_0()  GPIO_PORT_I2C->BSRR = (uint32_t)I2C_SCL_PIN << 16U         // SCL = 0 
 
// #define I2C_SDA_1()  GPIO_PORT_I2C->BSRR = I2C_SDA_PIN                                          // SDA = 1 
// #define I2C_SDA_0()  GPIO_PORT_I2C->BSRR = (uint32_t)I2C_SDA_PIN << 16U         // SDA = 0 

// #define I2C_SDA_READ()  (GPIO_PORT_I2C->IDR & I2C_SDA_PIN)                     // 读SDA口线状态 
// #define I2C_SCL_READ()  (GPIO_PORT_I2C->IDR & I2C_SCL_PIN)                    // 读SCL口线状态 


#define I2C_SCL_1()  LL_GPIO_SetOutputPin(GPIO_PORT_I2C,   I2C_SCL_PIN)                                         // SCL = 1 
#define I2C_SCL_0()  LL_GPIO_ResetOutputPin(GPIO_PORT_I2C, I2C_SCL_PIN)         // SCL = 0 
#define I2C_SDA_1()  LL_GPIO_SetOutputPin(GPIO_PORT_I2C,   I2C_SDA_PIN)                         // SDA = 1 
#define I2C_SDA_0()  LL_GPIO_ResetOutputPin(GPIO_PORT_I2C, I2C_SDA_PIN)         // SDA = 0 

#define I2C_SDA_READ()  (LL_GPIO_ReadInputPort(GPIO_PORT_I2C) & I2C_SDA_PIN)     // 读SDA口线状态 
#define I2C_SCL_READ()  (LL_GPIO_ReadInputPort(GPIO_PORT_I2C) & I2C_SCL_PIN)      // 读SCL口线状态 

 
#define NOP1()  __nop()
#define NOP2()  NOP1(),NOP1()
#define NOP3()  NOP2(),NOP1()
#define NOP4()  NOP3(),NOP1()
#define NOP5()  NOP4(),NOP1()
#define NOP6()  NOP5(),NOP1()
#define NOP7()  NOP6(),NOP1()
#define NOP8()  NOP7(),NOP1()
#define NOP9()  NOP8(),NOP1()
#define NOP10() NOP9(),NOP1()
#define NOP11() NOP10(),NOP1()
#define NOP12() NOP11(),NOP1()
#define NOP13() NOP12(),NOP1()
#define NOP14() NOP13(),NOP1()
#define NOP15() NOP14(),NOP1()
#define NOP16() NOP15(),NOP1()
#define NOP17() NOP16(),NOP1()
#define NOP18() NOP17(),NOP1()
#define NOP19() NOP18(),NOP1()
#define NOP20() NOP19(),NOP1()
#define NOP21() NOP20(),NOP1()
#define NOP22() NOP21(),NOP1()
#define NOP23() NOP22(),NOP1()
#define NOP24() NOP23(),NOP1()
#define NOP25() NOP24(),NOP1()
#define NOP26() NOP25(),NOP1()
#define NOP27() NOP26(),NOP1()
#define NOP28() NOP27(),NOP1()
#define NOP29() NOP28(),NOP1()
#define NOP30() NOP29(),NOP1()
#define NOP31() NOP30(),NOP1()
#define NOP32() NOP31(),NOP1()
#define NOP33() NOP32(),NOP1()
#define NOP34() NOP33(),NOP1()
#define NOP35() NOP34(),NOP1()
#define NOP36() NOP35(),NOP1()
#define NOP37() NOP36(),NOP1()
#define NOP38() NOP37(),NOP1()
#define NOP39() NOP38(),NOP1()
#define NOP40() NOP39(),NOP1()
#define NOP(N)  NOP##N##0()

//I2C所有操作函数
               

uint8_t  I2C_Write_Byte(uint8_t deviceAddr, uint8_t regAddress, uint8_t content);
uint8_t  I2C_Read_Byte(uint8_t deviceAddr, uint8_t regAddress, uint8_t *content);
uint8_t  I2C_Write_Bytes(uint8_t deviceAddr, uint8_t regAddress, const uint8_t *content, uint16_t size);
uint8_t  I2C_Read_Bytes(uint8_t deviceAddr, uint8_t regAddress, uint8_t *content, uint16_t size);

#endif
