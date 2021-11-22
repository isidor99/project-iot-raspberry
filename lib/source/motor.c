#include "./../header/motor.h"


void initMotorController(uint32_t maxSpeed, uint32_t frequency) {

	gpioSetPWMfrequency(MOTOR_A, frequency);
	gpioSetPWMrange(MOTOR_A, maxSpeed);

	gpioSetPWMfrequency(MOTOR_B, frequency);
	gpioSetPWMrange(MOTOR_B, maxSpeed);

	gpioSetMode(FORWARD_A_PIN, PI_OUTPUT);
	gpioSetMode(FORWARD_B_PIN, PI_OUTPUT);
	gpioSetMode(BACKWARD_A_PIN, PI_OUTPUT);
	gpioSetMode(BACKWARD_B_PIN, PI_OUTPUT);
}


void startMotor(uint8_t pin, uint32_t speed, uint8_t direction) {

	uint32_t maxSpeed = gpioGetPWMrange(pin);
	if (speed > maxSpeed) {
		perror("The set speed is higher than allowed\n");
		speed = maxSpeed;
	}

	uint8_t forwardPin = getDirectionPin(pin, DIRECTION_FORWARD);
	uint8_t backwardPin = getDirectionPin(pin, DIRECTION_BACKWARD);

	if (forwardPin != MOTOR_ERROR && backwardPin != MOTOR_ERROR) {

		if (direction == DIRECTION_FORWARD) {

			gpioWrite(forwardPin, HIGH);
			gpioWrite(backwardPin, LOW);

		} else if (direction == DIRECTION_BACKWARD) {

			gpioWrite(forwardPin, LOW);
			gpioWrite(backwardPin, HIGH);

		}
	}

	gpioPWM(pin, speed);
}


void stopMotor(uint8_t pin) {

	uint8_t forwardPin = getDirectionPin(pin, DIRECTION_FORWARD);
	uint8_t backwardPin = getDirectionPin(pin, DIRECTION_BACKWARD);

	if (forwardPin != MOTOR_ERROR && backwardPin != MOTOR_ERROR) {

		gpioWrite(forwardPin, LOW);
		gpioWrite(backwardPin, LOW);

		setMotorSpeed(pin, 0);
	}
}


void setMotorSpeed(uint8_t pin, uint32_t speed) {

	uint32_t maxSpeed = gpioGetPWMrange(pin);

	if (speed > maxSpeed) {
		perror("The set speed is higher than allowed\n");
		speed = maxSpeed;
	}

	gpioPWM(pin, speed);
}


void setMotorDirection(uint8_t pin, uint8_t direction) {

	stopMotor(pin);

	uint8_t forwardPin = getDirectionPin(pin, DIRECTION_FORWARD);
	uint8_t backwardPin = getDirectionPin(pin, DIRECTION_BACKWARD);

	if (direction == DIRECTION_FORWARD) {

		gpioWrite(forwardPin, HIGH);
		gpioWrite(backwardPin, LOW);

	} else if (direction == DIRECTION_BACKWARD) {

		gpioWrite(forwardPin, LOW);
		gpioWrite(backwardPin, HIGH);
	}
}


static uint8_t getDirectionPin(uint8_t pin, uint8_t direction) {

	if (pin == MOTOR_A) {
		if (direction == DIRECTION_FORWARD)
			return FORWARD_A_PIN;
		else if (direction == DIRECTION_BACKWARD)
			return BACKWARD_A_PIN;
	} else if (pin == MOTOR_B) {
		if (direction == DIRECTION_FORWARD)
			return FORWARD_B_PIN;
		else if (direction == DIRECTION_BACKWARD)
			return BACKWARD_B_PIN;
	}

	return MOTOR_ERROR;
}
