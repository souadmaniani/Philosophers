#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
typedef struct s_args
{
    int	nb_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	double	nb_must_eat;
	pthread_mutex_t number_eat;
	int *counter;
}               t_args;

typedef struct s_philo
{
	int index;
	t_args args;
	long last_eat;
	pthread_mutex_t *locks;
}			t_philo;

int	ft_atoi(const char *str);
long time_diff(struct timeval *start);
long time_to_ms(struct timeval *time);
long last_eat(struct timeval *start, struct timeval *end);
void				*philo_actions(void *arg);