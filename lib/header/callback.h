#ifndef CALLBACK_H
#define CALLBACK_H

#include <stdio.h>
#include <pthread.h>
#include <curl/curl.h>
#include <unistd.h>
#include <stdint.h>

#include "./client.h"

typedef struct arguments {
	CURL *curl;
	pthread_mutex_t *lock;
	uint32_t sleep;
} Arguments;

void* temperatureThreadCallback(void *args);

#endif
