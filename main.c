#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>
#include <signal.h>
#include <curl/curl.h>
#include <pthread.h>

#include "lib/header/pca.h"
#include "lib/header/motor.h"
#include "lib/header/client.h"
#include "lib/header/callback.h"

#define VALUE_LOW	0
#define VALUE_HIGH	1

#define DEVICE_ID	1

static volatile uint8_t run = 1;

void setup();
void clean();
void signalHandler(int arg);

CURL *curl;
pthread_mutex_t curlLock;

int main(int argc, char** argv) {

	// thread declaration
	pthread_t temperatureThread;

	// system setup
	setup();

	// create argument structure
	Arguments args;
	args.lock = &curlLock;
	args.sleep = 60;
	args.curl = curl;

	//
	//

	// create thread
	int err = pthread_create(&temperatureThread, NULL, &temperatureThreadCallback, (void *) &args);

	if (err)
		perror("Error creating temperature thread");

	// set signal handler
	gpioSetSignalFunc(SIGINT, signalHandler);

	// init motor controller
	initMotorController(5000, 1000);

	startMotor(MOTOR_A, 5000, DIRECTION_FORWARD);

	while (run);


	clean();

	return 0;
}

//
//
void setup() {

	// global init
	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();

	// init curl mutex
	if (pthread_mutex_init(&curlLock, NULL) != 0) {
		perror("CURL mutex error");
		exit(1);
	}

	// init gpio
	if (gpioInitialise() < 0) {
		printf("pigpio initialisation failed\n");
		exit(1);
	}

	// check curl
	if (!curl) {
		printf("curl initialisation failed\n");
		curl_global_cleanup();
		exit(1);
	}
}


void clean() {

	// destroy mutex
	pthread_mutex_destroy(&curlLock);

	// terminate gpio
	gpioTerminate();

	// clear curl
	curl_easy_cleanup(curl);

	// clear global curl
	curl_global_cleanup();
}


void signalHandler(int arg) {
	printf("\nTerminating...\n");
	run = 0;
	stopMotor(MOTOR_A);
	stopMotor(MOTOR_B);
}

