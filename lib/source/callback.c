#include "./../header/callback.h"

void* temperatureThreadCallback(void *p) {

	Arguments *args = (Arguments *) p;

	while (1) {

		pthread_mutex_lock(args->lock);

		addNewMeasurement(args->curl, 1, 1, 1, 40.334);

		pthread_mutex_unlock(args->lock);

		sleep(args->sleep);
	}
}
