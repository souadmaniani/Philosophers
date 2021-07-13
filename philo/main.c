#include "philo.h"

int	check_death(t_philo *philos, t_args	args)
{
	struct timeval	start;
	int				i;

	gettimeofday(&start, NULL);
	while (1)
	{
		i = -1;
		while (++i < args.nb_philos)
		{
			if (!philos[i].is_eating && ((philos[i].last_eat == -1
						&& time_diff(&start) > philos[i].args.time_to_die)
					|| ((time_diff(&start) - philos[i].last_eat)
						> philos[i].args.time_to_die)))
			{
				pthread_mutex_lock(philos[i].args.print);
				printf("%ld %d died \n", time_diff(&start), philos[i].index);
				return (1);
			}
			if (*philos[i].args.counter >= args.nb_must_eat * args.nb_philos)
				return (1);
		}
		usleep(100);
	}
	return (0);
}

int	get_arguments(int argc, t_args *args, char *argv[])
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
	args->print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(args->print, NULL);
	args->counter = malloc(sizeof(int));
	*(args->counter) = 0;
	return (0);
}

pthread_t	*create_threads(t_philo	*philos, t_args	args)
{
	pthread_t		*threads;
	int				error;
	int				i;

	i = -1;
	threads = malloc(args.nb_philos * sizeof(pthread_t));
	while (++i < args.nb_philos)
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

t_philo	*init_philos(t_args	args)
{
	int				i;
	t_philo			*philos;
	pthread_mutex_t	*locks;

	i = -1;
	locks = malloc(args.nb_philos * sizeof(pthread_mutex_t));
	while (++i < args.nb_philos)
		pthread_mutex_init(&locks[i], NULL);
	philos = malloc(args.nb_philos * sizeof(t_philo));
	i = -1;
	while (++i < args.nb_philos)
	{
		philos[i].index = i + 1;
		philos[i].args = args;
		philos[i].locks = locks;
		philos[i].last_eat = -1;
		philos[i].is_eating = 0;
	}
	return (philos);
}

int	main(int argc, char *argv[])
{
	t_args			args;
	t_philo			*philos;
	pthread_t		*threads;
	int				i;

	if (argc == 5 || argc == 6)
	{
		get_arguments(argc, &args, argv);
		philos = init_philos(args);
		threads = create_threads(philos, args);
		if (!threads)
			return (1);
		check_death(philos, args);
		usleep(1000 * args.nb_philos);
		free(threads);
	}
	else
		printf("Error args\n");
}
