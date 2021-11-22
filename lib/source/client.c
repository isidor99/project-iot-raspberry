#include "./../header/client.h"

uint8_t addNewMeasurement(CURL *curl, uint32_t devId, uint32_t typeId, uint32_t unitId, double val) {

	time_t timer;
	char dtime[26];
	struct tm *tmInfo;

	char *url;
	char *params;

	timer = time(NULL);
	tmInfo = localtime(&timer);
	strftime(dtime, 26, "%Y-%m-%d %H:%M:%S", tmInfo);

	asprintf(&url, "%s%s", BASE_URL, ENDPOINT_ADD_MEASUREMENT);
	asprintf(&params, "devId=%d&typeId=%d&unitId=%d&value=%lf&dtime=%s", devId, typeId, unitId, val, dtime);

	// set url
	curl_easy_setopt(curl, CURLOPT_URL, url);

	// set timeout
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, DEFAULT_TIMEOUT);

	// set params
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params);

	// perform
	CURLcode res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		perror(curl_easy_strerror(res));
		return POST_ERROR;
	}

	return POST_SUCCESS;
}
