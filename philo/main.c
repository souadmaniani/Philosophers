#include "philo.h"

int check_death(t_philo *philos, t_args			args)
{
	struct timeval start;

	gettimeofday(&start, NULL);
	while (1)
	{
		for (int i = 0; i < args.nb_philos; i++)
		{
			// pthread_mutex_lock(&philos[i].eating);
			if (!philos[i].is_eating && (( time_diff(&start) > philos[i].args.time_to_die && philos[i].last_eat == -1) 
				|| ( ( time_diff(&start) - philos[i].last_eat) > philos[i].args.time_to_die )))
			{
				*(args.dead) = 1;
				printf("%ld %d \e[1;31m died \e[0m\n", time_diff(&start), philos[i].index);
				//die_msg(pthread_mutex_t print, start, philo[i]);
				return (1);
				// pthread_mutex_unlock(philos[i].eating);
			}
			if (*philos[i].args.counter >= args.nb_must_eat * args.nb_philos)
					return (1);
		}
		usleep(100);
	}
	return (0);
}

int get_arguments(int argc, t_args *args, char *argv[])
{
	args->nb_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->nb_must_eat = ft_atoi(argv[5]);
	else
		args->nb_must_eat = 1.0 / 0.0;
	pthread_mutex_init(&args->number_eat, NULL);
	args->counter = malloc(sizeof(int));
	*(args->counter) = 0;
	args->dead = malloc(sizeof(int));
	*(args->dead) = 0;
	return (0);
}

pthread_t	* create_threads(t_philo	*philos, t_args	args)
{
	pthread_t		*threads;
	int				error;

	threads = malloc(args.nb_philos * sizeof(pthread_t));
	for (int i = 0; i < args.nb_philos; i++)
	{
		error = pthread_create(&threads[i], NULL, philo_actions, &philos[i]);
		if (error != 0)
		{
			printf("Thread can't be created \n");
			return (NULL);
		}
	}
	return (threads);
}

t_philo *init_philos(t_args	args)
{
	int				i;
	t_philo			*philos;
	pthread_mutex_t *locks;

	locks = malloc(args.nb_philos * sizeof(pthread_mutex_t));
	for (i = 0; i < args.nb_philos; i++)
		pthread_mutex_init(&locks[i], NULL);
	philos = malloc(args.nb_philos * sizeof(t_philo));
	for (i = 0; i < args.nb_philos; i++)
	{
		philos[i].index = i + 1;
		philos[i].args = args;
		philos[i].locks = locks;
		philos[i].last_eat = -1;
	}
	return (philos);
}

int main(int argc, char *argv[])
{
	t_args			args;
	t_philo			*philos;
	pthread_t		*threads;

	if (argc == 5 || argc == 6)
	{
		get_arguments(argc, &args, argv);
		philos = init_philos(args);
		threads = create_threads(philos, args);
		if (!threads)
			return (1);
		check_death(philos, args);
		// for (int i = 0; i < args.nb_philos; i++)
		// {
		// 	free(threads[i]);
		// 	threads[i] = NULL;
		// }
		// free(threads);
	}
	else
		printf("Error args\n");
}
