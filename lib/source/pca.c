#include "./../header/pca.h"


void initialize(uint32_t i2cHandle) {

        float freq = getFrequency(i2cHandle);
        uint8_t value = i2cReadByteData(i2cHandle, PCA9685_RA_MODE1);
        if (value < 0)
                perror("Can't init PCA9685 device. i2c read\n");

	printf("%d\n", value);

        value &= PCA9685_MODE1_AI_BIT_MASK;
        value |= ~PCA9685_MODE1_AI_BIT_MASK;

	printf("%d\n", value);

        int res = i2cWriteByteData(i2cHandle, PCA9685_RA_MODE1, value);
        if (res != 0)
                perror("Can't init PCA9685 device. i2c write\n");

        restart(i2cHandle);
}


uint8_t testConnection(uint32_t i2cHandle) {
        int res = i2cReadByteData(i2cHandle, PCA9685_RA_PRE_SCALE);
        if (res >= 0)
                return PCA9685_CONNECTED;
        return PCA9685_CONNECTION_ERROR;
}


float getFrequency(uint32_t i2cHandle) {
        uint8_t data = i2cReadByteData(i2cHandle, PCA9685_RA_PRE_SCALE);
        if (data < 0) {
                perror("Can't read frequency\n");
                return PCA9685_READ_FREQUENCY_ERROR;
        }

        return 24576000.f / 4096.f / (data + 1);
}


void setFrequency(uint32_t i2cHandle, float frequency) {
        pcaSleep(i2cHandle);
        usleep(10000);

        uint8_t prescale = roundf(24576000.f / 4096.f / frequency) - 1;
        int res = i2cWriteByteData(i2cHandle, PCA9685_RA_PRE_SCALE, prescale);
        if (res != 0)
                perror("Error setting frequency\n");

        restart(i2cHandle);
}


void pcaSleep(uint32_t i2cHandle) {

        uint8_t value = i2cReadByteData(i2cHandle, PCA9685_RA_MODE1);

        if (value < 0) {
                value &= PCA9685_MODE1_SLEEP_BIT_MASK;
                value |= ~PCA9685_MODE1_SLEEP_BIT_MASK;

                int res = i2cWriteByteData(i2cHandle, PCA9685_RA_MODE1, value);
                if (res != 0)
                        perror("Can't write sleep bit\n");
        } else
                perror("Can't write sleep bit\n");
}


void restart(uint32_t i2cHandle) {

        int res = i2cWriteByteData(i2cHandle, PCA9685_RA_MODE1, PCA9685_RESTART_STEP_1);
        if (res != 0)
                perror("Restart step 1 error\n");

        res = i2cWriteByteData(i2cHandle, PCA9685_RA_MODE1, PCA9685_RESTART_STEP_2);
        if (res != 0)
                perror("Restart step 2 error\n");

        res = i2cWriteByteData(i2cHandle, PCA9685_RA_MODE1, PCA9685_RESTART_STEP_3);
        if (res != 0)
                perror("Restart step 3 error\n");
}


void setPwmWithOffest(uint32_t i2cHandle, uint8_t channel, uint16_t offset, uint16_t length) {

        uint8_t data[4] = { 0, 0, 0, 0 };
        if (length == 0)
                data[3] = 0x10;
        else if (length >= 4096)
                data[1] = 0x10;
        else {
                data[0] = offset & 0xff;
                data[1] = offset >> 8;
                data[2] = length & 0xff;
                data[3] = length >> 8;
        }

        int res = i2cWriteBlockData(i2cHandle, PCA9685_RA_LED0_ON_L + 4 * channel, data, sizeof(data));
        if (res != 0)
                perror("Error setting up PWM\n");
}


void setPwm(uint32_t i2cHandle, uint8_t channel, uint16_t length) {
        setPwmWithOffest(i2cHandle, channel, 0, length);
}


void setPwm_mS(uint32_t i2cHandle, uint8_t channel, float length_mS) {
        float frequency = getFrequency(i2cHandle);
        setPwm(i2cHandle, channel, round((length_mS * 4096.f) / (1000.f / frequency)));
}


void setPwm_uS(uint32_t i2cHandle, uint8_t channel, float length_uS) {
        float frequency = getFrequency(i2cHandle);
        setPwm(i2cHandle, channel, round((length_uS * 4096.f) / (1000000.f / frequency)));
}


void setAllPwmWithOffest(uint32_t i2cHandle, uint16_t offset, uint16_t length) {
        uint8_t data[4] = {
                offset & 0xff,
                offset >> 8,
                length & 0xff,
                length >> 8
        };

        int res = i2cWriteBlockData(i2cHandle, PCA9685_RA_ALL_LED_ON_L, data, sizeof(data));
        if (res != 0)
                perror("Error setting up all PWM\n");
}


void setAllPwm(uint32_t i2cHandle, uint16_t length) {
        setAllPwmWithOffest(i2cHandle, 0, length);
}


void setAllPwm_mS(uint32_t i2cHandle, float length_mS) {
        float frequency = getFrequency(i2cHandle);
        setAllPwm(i2cHandle, round((length_mS * 4096.f) / (1000.f / frequency)));
}


void setAllPwm_uS(uint32_t i2cHandle, float length_uS) {
        float frequency = getFrequency(i2cHandle);
        setAllPwm(i2cHandle, round((length_uS * 4096.f) / (1000000.f / frequency)));
}
