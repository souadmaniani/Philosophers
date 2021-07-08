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

float time_diff(struct timeval *start, struct timeval *end)
{
    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}

long timestamp_in_ms(struct timeval *start)
{
	return (start->tv_sec * 1e3 + start->tv_usec * 1e-3);
}
// thread for philo
void *philo_actions(void *arg)
{
	pthread_mutex_t lock;
	t_philo *philo = (t_philo*)arg;

	// khass yn3sso hadou f lowwl
	if (!((*philo).index % 2))
		usleep(10);
	// do activities
	struct timeval start;
	gettimeofday(&start, NULL);
	// while (time_diff(&start, &end) < (*philo).args.time_to_die)
	while ( 1 )
	{
		// LOCK FIRST FORK
		pthread_mutex_lock(&philo->locks[(*philo).index]); 
		printf("%ld %d has taken a fork\n", timestamp_in_ms(&start), (*philo).index);
		// LOCK SECOND FORK
		pthread_mutex_lock(&philo->locks[(*philo).index] + 1);
		printf("%ld %d has taken a fork\n", timestamp_in_ms(&start), (*philo).index);
		// gettimeofday(&start, NULL);
		// time to eat
		printf("%ld %d is eating\n", timestamp_in_ms(&start), (*philo).index);
		usleep((*philo).args.time_to_eat * 1000);
		pthread_mutex_unlock(&lock);
		/***********************************************/
		// time to sleep
		printf("%ld %d is sleeping\n", timestamp_in_ms(&start), (*philo).index);
		usleep((*philo).args.time_to_sleep * 1000);
		/**********************************************/
		printf("%ld %d is thinking\n", timestamp_in_ms(&start), (*philo).index);
	}
	// printf("%d died\n", (*philo).index);
	return (NULL);
}

int main(int argc, char *argv[])
{
	t_args			args;
	int				i;
	pthread_t		*threads;
	t_philo			philo;
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
		locks = malloc(args.number_of_philosopher * sizeof(pthread_mutex_t));
		// INIT FORKS MUTEX
		for (i = 0; i < args.number_of_philosopher; i++)
			pthread_mutex_init(&locks[i], NULL);
		/***************************/
		philo.locks = locks;
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

