#ifndef PCA_H
#define PCA_H

#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>
#include <math.h>
#include <unistd.h>

#define PCA9685_DEFAULT_ADDRESS     0x40 // All address pins low, Navio default

#define PCA9685_RA_MODE1            0x00
#define PCA9685_RA_MODE2            0x01
#define PCA9685_RA_LED0_ON_L        0x06
#define PCA9685_RA_LED0_ON_H        0x07
#define PCA9685_RA_LED0_OFF_L       0x08
#define PCA9685_RA_LED0_OFF_H       0x09
#define PCA9685_RA_ALL_LED_ON_L     0xFA
#define PCA9685_RA_ALL_LED_ON_H     0xFB
#define PCA9685_RA_ALL_LED_OFF_L    0xFC
#define PCA9685_RA_ALL_LED_OFF_H    0xFD
#define PCA9685_RA_PRE_SCALE        0xFE

#define PCA9685_MODE1_RESTART_BIT   7
#define PCA9685_MODE1_EXTCLK_BIT    6
#define PCA9685_MODE1_AI_BIT        5
#define PCA9685_MODE1_SLEEP_BIT     4
#define PCA9685_MODE1_SUB1_BIT      3
#define PCA9685_MODE1_SUB2_BIT      2
#define PCA9685_MODE1_SUB3_BIT      1
#define PCA9685_MODE1_ALLCALL_BIT   0

#define PCA9685_RESTART_STEP_1            0x10
#define PCA9685_RESTART_STEP_2            0x50
#define PCA9685_RESTART_STEP_3            0x70

#define PCA9685_MODE1_AI_BIT_MASK       0xdf
#define PCA9685_MODE1_SLEEP_BIT_MASK    0xef

#define PCA9685_MODE2_INVRT_BIT     4
#define PCA9685_MODE2_OCH_BIT       3
#define PCA9685_MODE2_OUTDRV_BIT    2
#define PCA9685_MODE2_OUTNE1_BIT    1
#define PCA9685_MODE2_OUTNE0_BIT    0

#define PCA9685_CONNECTED                       1
#define PCA9685_CONNECTION_ERROR                -1
#define PCA9685_READ_FREQUENCY_ERROR		-2


void initialize(uint32_t i2cHandle);
uint8_t testConnection(uint32_t i2cHandle);

float getFrequency(uint32_t i2cHandle);
void setFrequency(uint32_t i2cHandle, float frequency);

void pcaSleep(uint32_t i2cHandle);
void restart(uint32_t i2cHandle);

void setPwmWithOffset(uint32_t i2cHandle, uint8_t channel, uint16_t offset, uint16_t length);
void setPwm(uint32_t i2cHandle, uint8_t channel, uint16_t length);
void setPwm_mS(uint32_t i2cHandle, uint8_t channel, float length_mS);
void setPwm_uS(uint32_t i2cHandle, uint8_t channel, float length_uS);

void setAllPwmWithOffset(uint32_t i2cHandle, uint16_t offset, uint16_t length);
void setAllPwm(uint32_t i2cHandle, uint16_t length);
void setAllPwm_mS(uint32_t i2cHandle, float length_mS);
void setAllPwm_uS(uint32_t i2cHandle, float length_uS);

#endif
