#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
typedef struct s_args
{
    int	number_of_philosopher;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}               t_args;

typedef struct s_philo
{
	int index;
	t_args args;
}			t_philo;

int	ft_atoi(const char *str);