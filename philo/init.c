/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaas <sklaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 00:34:24 by sklaas            #+#    #+#             */
/*   Updated: 2025/07/07 21:47:12 by sklaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_data(t_data *data, char **argv, int argc)
{
	data->nb_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->time_to_think = (data->time_to_die - data->time_to_eat \
		- data->time_to_sleep) * 0.9;
	if (argc == 6)
		data->nb_must_eat = ft_atol(argv[5]);
	else
		data->nb_must_eat = -1;
	data->someone_died = false;
	data->start_time = get_time();
}

void	init_all(t_data *data, t_philo *philo, char **argv, int argc)
{
	int	i;

	i = -1;
	init_data(data, argv, argc);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return ;
	while (++i < data->nb_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->meals_eaten_mutex, NULL);
	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_init(&philo[i].meal_mutex, NULL);
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].time_last_meal = data->start_time;
		philo[i].meals_eaten = 0;
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
	}
	data->philo = philo;
}

int	join_all_threads(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (printf("Error joining routine threads\n"), 1);
	}
	if (pthread_join(data->monitor_thread, NULL) != 0)
		return (printf("Error joining monitor threads\n"), 1);
	return (0);
}

void	*create_one_philo(t_philo *philo)
{
	if (pthread_create(&philo[0].thread, NULL, routine, &philo[0]) != 0)
		return (printf("Error creating routine thread\n"), NULL);
	pthread_join(philo[0].thread, NULL);
	return (NULL);
}

void	*create_threads(t_data *data, t_philo *philo)
{
	int	i;

	if (data->nb_philo == 1)
		return (create_one_philo(philo), NULL);
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
			return (printf("Error creating routine threads\n"), NULL);
	}
	if (pthread_create(&data->monitor_thread, NULL, &monitor, data) != 0)
		return (printf("Error creating meal monitoring thread\n"), NULL);
	i = -1;
	if (join_all_threads(data, philo))
		return (NULL);
	return (NULL);
}
