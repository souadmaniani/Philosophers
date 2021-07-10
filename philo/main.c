
// time_to_die: is in milliseconds, if a philosopher doesn’t 
// start eating ’time_to_die’milliseconds after starting his
// last meal or the beginning of the simulation, it dies


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

int number_eat = 0;
void				*philo_actions(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	// khass lli even yn3asss f depart (0, 2, 4)  
	if ( !( philo->index % 2 ) )
		usleep(10);
	// time reference 
	struct timeval start;
	long time_now;
	pthread_mutex_t lock;
	pthread_mutex_init(&lock, NULL);
	gettimeofday(&start, NULL);
	while (1)
	{
		printf("%ld %d is thinking\n", time_diff(&start), philo->index);
		int left = (philo->index + philo->args.number_of_philosopher - 1) % (philo->args.number_of_philosopher );
		/*********************************** EAT **************************************************************/
		pthread_mutex_lock(&philo->locks[left]);
		time_now = time_diff(&start);
		// does not start eating yet OR daz time to die after last meal 
		if ((time_now >= philo->args.time_to_die && !philo->last_eat ) || (time_now - philo->last_eat) >= philo->args.time_to_die)
		{
			printf("time now: %ld ms , %d \e[1;31m died \e[0m\n", time_now, philo->index);
			exit(1);
		}
		printf("time_now: %ld %ld %d has taken a fork\n",time_now, time_diff(&start), philo->index);
		pthread_mutex_lock(&philo->locks[philo->index]);
		printf("%ld %d has taken a fork\n", time_diff(&start), philo->index);
		printf("%ld %d is eating\n", time_diff(&start), philo->index);
		/*****************************************************************************************************/

		/*********************************** INCREMENT NUMBER OF EAT *****************************************/
		struct timeval eat_time;
		gettimeofday(&eat_time, NULL);
		philo->last_eat = last_eat(&start, &eat_time);
		number_eat += 1;
		if (number_eat >= philo->args.number_of_times_each_philosopher_must_eat * philo->args.number_of_philosopher)
			exit(1);
		/****************************************************************************************************/

		/***************************** TIME OF EATING AND UNLOCK FORKS **************************************/
		time_now = time_diff(&start);
		if (philo->args.time_to_eat > philo->args.time_to_die)
			usleep(philo->args.time_to_die * 1e3);
		else
			usleep(philo->args.time_to_eat * 1e3);
		/*---------------------------------------------------------------------------------------------------*/
		pthread_mutex_unlock(&philo->locks[left]);
		pthread_mutex_unlock(&philo->locks[philo->index]);
		usleep(philo->args.time_to_sleep * 1e3);
		/****************************************************************************************************/
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
		philos = malloc(args.number_of_philosopher * sizeof(t_philo));
		for (int i = 0; i < args.number_of_philosopher; i++)
		{
			philos[i].locks = locks;
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

