#include "philo.h"

long time_diff(struct timeval *start)
{
	struct timeval time;
	gettimeofday(&time, NULL);
    return (time.tv_sec - start->tv_sec)*1e3 + 1e-3*(time.tv_usec - start->tv_usec);
}

long time_to_ms(struct timeval *time)
{
	return (time->tv_sec * 1e3 + 1e-3 * time->tv_usec);
}

long last_eat(struct timeval *start, struct timeval *end)
{
	 return (end->tv_sec - start->tv_sec)*1e3 + 1e-3*(end->tv_usec - start->tv_usec);
}