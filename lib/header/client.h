#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <curl/curl.h>
#include <time.h>
#include <stdint.h>

#define BASE_URL			"http://192.168.1.180:11450"
#define DEFAULT_TIMEOUT			5L

#define ENDPOINT_ADD_MEASUREMENT	"/measurement/new"

#define POST_ERROR			0x01
#define POST_SUCCESS			0x02

uint8_t addNewMeasurement(CURL *curl, uint32_t devId, uint32_t typeId, uint32_t unitId, double val);

#endif
