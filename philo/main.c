#include "philo.h"

void				*philo_actions(void *arg)
{
	struct timeval start;
	t_philo *philo = (t_philo *)arg; 
	if (philo->index % 2)
		usleep(500);
	gettimeofday(&start, NULL);
	while (1)
	{
		printf("%ld %d is thinking\n", time_diff(&start), philo->index);
		int left = (philo->index + philo->args.number_of_philosopher - 1) % (philo->args.number_of_philosopher );
		pthread_mutex_lock(&philo->locks[left]);
		printf("%ld %d has taken a fork\n", time_diff(&start), philo->index);
		pthread_mutex_lock(&philo->locks[philo->index]);
		printf("%ld %d has taken a fork\n", time_diff(&start), philo->index);
		printf("%ld %d is eating\n", time_diff(&start), philo->index);
		philo->last_eat = time_diff(&start);
		pthread_mutex_lock(&philo->args.number_eat);
		*(philo->args.counter) = *(philo->args.counter) + 1;
		pthread_mutex_unlock(&philo->args.number_eat);
		usleep(philo->args.time_to_eat * 1e3);
		pthread_mutex_unlock(&philo->locks[left]);
		pthread_mutex_unlock(&philo->locks[philo->index]);
		usleep(philo->args.time_to_sleep * 1e3);
	}
	return (NULL);
}
int main(int argc, char *argv[])
{
	t_args			args;
	int				i;
	pthread_t		*threads;
	t_philo			*philos;
	int				error;
	pthread_mutex_t *locks;

	if (argc == 5 || argc == 6)
	{
		pthread_mutex_init(&args.number_eat, NULL);
		args.number_of_philosopher = ft_atoi(argv[1]);
		args.time_to_die = ft_atoi(argv[2]);
		args.time_to_eat = ft_atoi(argv[3]);
		args.time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			args.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		else
			args.number_of_times_each_philosopher_must_eat = 1.0 / 0.0;
		
		args.counter = malloc(sizeof(int));
		*(args.counter) = 0;
		locks = malloc(args.number_of_philosopher * sizeof(pthread_mutex_t));
		for (i = 0; i < args.number_of_philosopher; i++)
			pthread_mutex_init(&locks[i], NULL);
		philos = malloc(args.number_of_philosopher * sizeof(t_philo));
		for (int i = 0; i < args.number_of_philosopher; i++)
		{
			philos[i].locks = locks;
			philos[i].last_eat = -1;
		}
		threads = malloc(args.number_of_philosopher * sizeof(pthread_t));
		// TIME 0
		for (int i = 0; i < args.number_of_philosopher; i++)
		{
			philos[i].index = i;
			philos[i].args = args;
			error = pthread_create(&threads[i], NULL, philo_actions, &philos[i]);
			if (error != 0)
			{
				printf("\nThread can't be created : [%s]", strerror(error));
				return (0);
			}
		}
		struct timeval start;
		gettimeofday(&start, NULL);
		while (1)
		{
			for (int i = 0; i < args.number_of_philosopher; i++)
			{
				if ( args.number_of_philosopher == 1
					|| ( time_diff(&start) > philos[i].args.time_to_die && philos[i].last_eat == -1) 
					|| ((time_diff(&start) - philos[i].last_eat) > philos[i].args.time_to_die ) )
				{
					printf("%ld %d \e[1;31m died \e[0m\n", time_diff(&start), philos[i].index);
					return (1);
				}
				// usleep(10);
				if (*philos[i].args.counter >= args.number_of_times_each_philosopher_must_eat
					* args.number_of_philosopher)
					{
						return (1);
					}
			}
			usleep(100);
		}	
	}
	else
		printf("Error args\n");
}

