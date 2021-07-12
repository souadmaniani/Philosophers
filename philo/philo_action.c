#include "philo.h"

int  eat(t_philo *philo, int left, int right, struct timeval start)
{
	left = (philo->args.nb_philos + philo->index - 2) % (philo->args.nb_philos);
	right = philo->index - 1;
	pthread_mutex_lock(&philo->locks[left]);
	printf("%ld %d has taken a fork\n", time_diff(&start), philo->index);
	pthread_mutex_lock(&philo->locks[right]);
	printf("%ld %d has taken a fork\n", time_diff(&start), philo->index);
	printf("%ld %d is eating\n", time_diff(&start), philo->index);
	philo->last_eat = time_diff(&start);
	pthread_mutex_lock(&philo->args.number_eat);
	*(philo->args.counter) = *(philo->args.counter) + 1;
	pthread_mutex_unlock(&philo->args.number_eat);
	usleep(philo->args.time_to_eat * 1e3);
	return (0);
}

void				*philo_actions(void *arg)
{
	struct timeval start;
	int left;
	int right;

	gettimeofday(&start, NULL);
	t_philo *philo = (t_philo *)arg; 
	if (philo->index % 2)
		usleep(500);
	while (1)
	{
		printf("%ld %d is thinking\n", time_diff(&start), philo->index);
		left = (philo->args.nb_philos + philo->index - 2) % (philo->args.nb_philos);
		right = philo->index - 1;
		eat(philo, left, right, start);
		pthread_mutex_unlock(&philo->locks[left]);
		pthread_mutex_unlock(&philo->locks[right]);
		printf("%ld %d is sleeping\n", time_diff(&start), philo->index);
		usleep(philo->args.time_to_sleep * 1e3);
	}
	return (NULL);
}
