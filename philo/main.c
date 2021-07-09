// Philosophers don’t speak with each other.
// number_of_philosophers (1 ... )
// time_to_die
// time_to_eat
// time_to_sleep
// [number_of_times_each_philosopher_must_eat]

// timestamp_in_ms X has taken a fork
// timestamp_in_ms X is eating
// timestamp_in_ms X is sleeping
// timestamp_in_ms X is thinking
// timestamp_in_ms X died

// Each philosopher should be a thread

// To avoid philosophers duplicating forks,
// you should protect the forks state with a mutex for each of them.
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

// thread for philo
int number_eat = 0;
void *philo_actions(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	// khass lli even yn3asss (0, 2, 4) 
	if ( !( philo->index % 2 ) )
		usleep(500);
	// time reference 
	struct timeval start;
	long time_now;
	gettimeofday(&start, NULL);
	while (1)
	{
		int left = (philo->index + philo->args.number_of_philosopher - 1) % (philo->args.number_of_philosopher );
		time_now = time_diff(&start);
		if (time_now - philo->last_eat > philo->args.time_to_die)
		{
			printf("diff: %ld ms , %d \e[1;31m died \e[0m\n", time_now - philo->last_eat, philo->index); 
			exit(1);
		}
		pthread_mutex_lock(&philo->locks[left]); 
		printf("%ld %d has taken a fork\n", time_diff(&start), philo->index);
		pthread_mutex_lock(&philo->locks[philo->index]);
		printf("%ld %d has taken a fork\n", time_diff(&start), philo->index);
		printf("%ld %d is eating\n", time_diff(&start), philo->index);
		number_eat +=1;
		if (number_eat >= philo->args.number_of_times_each_philosopher_must_eat * philo->args.number_of_philosopher)
			exit(1);
		// printf("*******************************************************\n");
		usleep(philo->args.time_to_eat * 1000);
		// printf("%ld %d  end eating \n", time_diff(&start), philo->index);
		/****** last eat ********/
		struct timeval eat_time;
		gettimeofday(&eat_time, NULL);
		philo->last_eat = eat_time.tv_sec * 1e3 + eat_time.tv_usec * 1e-3;
		/************************/
		pthread_mutex_unlock(&philo->locks[left]);
		pthread_mutex_unlock(&philo->locks[philo->index]);
		printf("%ld %d is sleeping\n", time_diff(&start), philo->index);
		usleep(philo->args.time_to_sleep * 1000);
		printf("%ld %d is thinking\n", time_diff(&start), philo->index);
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
		philos = malloc(sizeof(t_philo ) * args.number_of_philosopher);
		for (int i = 0; i < args.number_of_philosopher; i++)
		{
			philos[i].locks = &locks[i];
			philos[i].last_eat = 0;
		}
		threads = malloc(args.number_of_philosopher * sizeof(pthread_t));
		// TIME 0
		struct timeval start;
		gettimeofday(&start, NULL);
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
		for (int i = 0; i < args.number_of_philosopher; i++)
			pthread_join(threads[i], NULL);
		// if (check_number_time_eating(philos))
		// 	exit(1);
		printf("main thread\n");
	}
	else
		printf("Error args\n");
}

