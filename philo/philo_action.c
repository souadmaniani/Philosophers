#include "philo.h"

void	print_state(char *str, struct timeval start, int index,
	pthread_mutex_t *print)
{
	pthread_mutex_lock(print);
	printf("%ld %d %s", time_diff(&start), index, str);
	pthread_mutex_unlock(print);
}

int	eat(t_philo *philo, int left, int right, struct timeval start)
{
	left = (philo->args.nb_philos + philo->index - 2) % (philo->args.nb_philos);
	right = philo->index - 1;
	pthread_mutex_lock(&philo->locks[left]);
	print_state("has taken a fork\n", start, philo->index, philo->args.print);
	pthread_mutex_lock(&philo->locks[right]);
	print_state("has taken a fork\n", start, philo->index, philo->args.print);
	philo->is_eating = 1;
	print_state("is eating\n", start, philo->index, philo->args.print);
	philo->last_eat = time_diff(&start);
	pthread_mutex_lock(&philo->args.number_eat);
	*(philo->args.counter) = *(philo->args.counter) + 1;
	pthread_mutex_unlock(&philo->args.number_eat);
	usleep(philo->args.time_to_eat * 1e3);
	philo->is_eating = 0;
	return (0);
}

void	*philo_actions(void *arg)
{
	struct timeval	start;
	int				left;
	int				right;
	t_philo			*philo;

	gettimeofday(&start, NULL);
	philo = (t_philo *)arg;
	if (philo->index % 2)
		usleep(500);
	while (1)
	{
		print_state("is thinking\n", start, philo->index, philo->args.print);
		left = (philo->args.nb_philos + philo->index - 2)
			% (philo->args.nb_philos);
		right = philo->index - 1;
		eat(philo, left, right, start);
		pthread_mutex_unlock(&philo->locks[left]);
		pthread_mutex_unlock(&philo->locks[right]);
		print_state("is sleeping\n", start, philo->index, philo->args.print);
		usleep(philo->args.time_to_sleep * 1e3);
	}
	return (NULL);
}
