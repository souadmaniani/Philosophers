#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
typedef struct s_args
{
    int	number_of_philosopher;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	double	number_of_times_each_philosopher_must_eat;
	pthread_mutex_t number_eat;
}               t_args;

typedef struct s_philo
{
	int index;
	t_args args;
	long last_eat;
	pthread_mutex_t *locks;
}			t_philo;

int	ft_atoi(const char *str);