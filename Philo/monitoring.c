/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaas <sklaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:39:40 by sklaas            #+#    #+#             */
/*   Updated: 2025/07/07 04:08:37 by sklaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*declare_sim_over(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->someone_died = true;
	pthread_mutex_unlock(&data->death_mutex);
	return (NULL);
}

void	*monitor_meals(void *arg)
{
	t_data	*data;
	t_philo	*philo;
	int		i;
	int		full;

	data = (t_data *)arg;
	philo = data->philo;
	while (true)
	{
		i = 0;
		full = 0;
		while (i < data->nb_philo)
		{
			if (philo[i].meals_eaten >= data->nb_must_eat)
				full++;
			i++;
		}
		if (full == data->nb_philo)
			return (declare_sim_over(data));
		usleep(1000);
	}
	return (NULL);
}

void	print_death(t_philo *philo, long now)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld Philosopher %d died\n",
		now - data->start_time, philo->id);
	pthread_mutex_unlock(&data->print_mutex);
}

void	*monitor_death(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	long	now;
	long	last_meal;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		now = get_time();
		pthread_mutex_lock(&data->death_mutex);
		if (data->someone_died)
			return (pthread_mutex_unlock(&data->death_mutex), NULL);
		pthread_mutex_lock(&philo->meal_mutex);
		last_meal = philo->time_last_meal;
		pthread_mutex_unlock(&philo->meal_mutex);
		if (now - last_meal >= data->time_to_die)
		{
			data->someone_died = true;
			print_death(philo, now);
			pthread_mutex_unlock(&data->death_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&data->death_mutex);
	}
}
