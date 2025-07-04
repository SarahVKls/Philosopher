/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaas <sklaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:55:24 by sklaas            #+#    #+#             */
/*   Updated: 2025/07/04 19:13:36 by sklaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	get_time(void)
{
	struct timeval	tv;
	long int		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	init_data(t_data *data, t_philo *philo, char **argv)
{
	int	i;

	i = 0;
	data->nb_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		data->nb_must_eat = ft_atol(argv[5]);
	//data->someone_died = 0;
	data->start_time = get_time();
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return ;

	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].time_last_meal = data->start_time;
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		i++;
	}
}

void	create_threads(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
			return (printf("Error creating threads\n"));
		//init monitors

	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (printf("error joining threads\n"));
	}
}

//Valid
// "+1'\0'"
// "1'\0'"

// invalid
// "'\0'"
// a1
// "++1"
// overflow


int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (argv[i][0] == '\0')
			return (0);
		while (argv[i][j])
		{
			if (argv[i][j] == '+')
			{
				if (argv[i][j + 1] == '+')
					return (0);
				j++;
			}
			if (ft_isdigit(argv[i][j]))
				j++;
			else
				return (0);
		}
		i++;
	}
	if (ft_atol(argv[3]) < 1 || ft_atol(argv[1]) < 1)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;

	data = malloc(sizeof(t_data));
	if (!data)
		return ;
	philo = malloc(sizeof(t_philo) * ft_atol(argv[1]));
	if (!philo)
		return ;
	if (argc < 5 || argc > 6)
		return (0);
	if (!check_args(argv))
		return (printf("ERROR : invalid args\n"), -1);
	init_data(data, philo, argv);
	create_threads(data, philo);
	return (0);
}
