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
// thread for philo
void *philo_actions(void *arg)
{
	pthread_mutex_t lock;
	int *x;
	t_philo *philo = (t_philo*)arg;
	pthread_mutex_init(&lock, NULL);
	// do activities
	// if ((*philo).index == 1 && )
	while (1)
	{
		pthread_mutex_lock(&lock); 
		printf( "%d has taken a fork\n", (*philo).index);
		pthread_mutex_unlock(&lock);
		pthread_mutex_lock(&lock);
		printf("%d has taken a fork\n", (*philo).index);
		pthread_mutex_unlock(&lock);
		printf("%d is eating\n", (*philo).index);
		usleep((*philo).args.time_to_eat * 1000);
		//think
	}
	return (NULL);
}

int main(int argc, char *argv[])
{
	t_args		args;
	int			i;
	pthread_t	*threads;
	t_philo		philo;
	int			error;

	if (argc == 5 || argc == 6)
	{
		args.number_of_philosopher = ft_atoi(argv[1]);
		args.time_to_die = ft_atoi(argv[2]);
		args.time_to_eat = ft_atoi(argv[3]);
		args.time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			args.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		threads = malloc(args.number_of_philosopher * sizeof(pthread_t));

		for (int i = 1; i <= args.number_of_philosopher; i++)
		{
			philo.index = i;
			philo.args = args;
			error = pthread_create(&threads[i], NULL, philo_actions, &philo);
			if (error != 0)
            		printf("\nThread can't be created : [%s]", strerror(error));
			pthread_join(threads[i], NULL);
			pthread_detach(threads[i]);
		}
		printf("main thread\n");
	}
	else
		printf("Error args\n");
}

