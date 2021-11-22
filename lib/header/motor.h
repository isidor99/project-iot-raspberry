#ifndef MOTOR_H
#define MOTOR_H

#include <stdio.h>
#include <pigpio.h>

#define MOTOR_A		14
#define MOTOR_B		15

#define FORWARD_A_PIN		6
#define FORWARD_B_PIN		19
#define BACKWARD_A_PIN		13
#define BACKWARD_B_PIN		26

#define MOTOR_ERROR		-11

#define DIRECTION_FORWARD	0x01
#define DIRECTION_BACKWARD	0x02

#define HIGH			1
#define LOW			0

void initMotorController(uint32_t maxSpeed, uint32_t frequnecy);

void startMotor(uint8_t pin, uint32_t speed, uint8_t direction);
void stopMotor(uint8_t pin);

void setMotorSpeed(uint8_t pin, uint32_t speed);
void setMotorDirection(uint8_t pin, uint8_t direction);


static uint8_t getDirectionPin(uint8_t pin, uint8_t direction);

#endif
