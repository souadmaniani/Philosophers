
// time_to_die: is in milliseconds, if a philosopher doesn’t 
// start eating ’time_to_die’milliseconds after starting his
// last meal or the beginning of the simulation, it dies
// 1 800 200 200 =====> should die
// 5 800 200 200 =====> no one should die
// 5 800 200 200 7 ===> no one should die 
// 2 410 200 200 =====> no one should die
// 4 310 200 100 =====> someone should die

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
// ./philo 5 100 200 200  
int number_eat = 0;

void				*philo_actions(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	// int *return_value = (int *)malloc(sizeof(int));
	// khass lli even yn3asss f depart (0, 2, 4)  
	if (philo->index % 2)
		usleep(100);
	// time reference 
	struct timeval start;
	long time_now;
	gettimeofday(&start, NULL);
	while (1)
	{
		printf("%ld %d is thinking\n", time_diff(&start), philo->index);
		int left = (philo->index + philo->args.number_of_philosopher - 1) % (philo->args.number_of_philosopher );
		/*********************************** EAT **************************************************************/
		pthread_mutex_lock(&philo->locks[left]);
		printf("%ld %d has taken a fork\n", time_diff(&start), philo->index);
		pthread_mutex_lock(&philo->locks[philo->index]);
		printf("%ld %d has taken a fork\n", time_diff(&start), philo->index);
		printf("%ld %d is eating\n", time_diff(&start), philo->index);
		struct timeval eat_time;
		gettimeofday(&eat_time, NULL);
		philo->last_eat = last_eat(&start, &eat_time);
		pthread_mutex_lock(&philo->args.number_eat);
		number_eat += 1;
		pthread_mutex_unlock(&philo->args.number_eat);
		// if (number_eat >= philo->args.number_of_times_each_philosopher_must_eat * philo->args.number_of_philosopher)
		// {
		// 	return 
		// }
		if (philo->args.time_to_eat > philo->args.time_to_die)
			usleep(philo->args.time_to_die * 1e3);
		else
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
		locks = malloc(args.number_of_philosopher * sizeof(pthread_mutex_t));
		for (i = 0; i < args.number_of_philosopher; i++)
			pthread_mutex_init(&locks[i], NULL);
		philos = malloc(args.number_of_philosopher * sizeof(t_philo));
		for (int i = 0; i < args.number_of_philosopher; i++)
		{
			philos[i].locks = locks;
			philos[i].last_eat = 0;
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
				usleep(100);
				// check death
				if ( args.number_of_philosopher == 1
					|| ( time_diff(&start) > philos[i].args.time_to_die && !philos[i].last_eat) 
					|| ((time_diff(&start) - philos[i].last_eat) > philos[i].args.time_to_die ) )
				{
					printf("%ld %d \e[1;31m died \e[0m\n", time_diff(&start), philos[i].index);
					return (1);
				}
				if ( number_eat >= philos[i].args.number_of_times_each_philosopher_must_eat * philos[i].args.number_of_philosopher )
				{
					return (1);
				}
			}
		}	
	}
	else
		printf("Error args\n");
}

