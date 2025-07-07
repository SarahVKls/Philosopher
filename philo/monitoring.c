/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaas <sklaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:39:40 by sklaas            #+#    #+#             */
/*   Updated: 2025/07/07 21:50:41 by sklaas           ###   ########.fr       */
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

static void	print_death(t_philo *philo, long now)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d died\n",
		now - data->start_time, philo->id);
	pthread_mutex_unlock(&data->print_mutex);
}

int	philo_is_dead(t_philo *philo)
{
	t_data	*data;
	long	now;
	long	last_meal;

	data = philo->data;
	pthread_mutex_lock(&philo->meal_mutex);
	last_meal = philo->time_last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	now = get_time();
	pthread_mutex_lock(&data->death_mutex);
	if (now - last_meal >= data->time_to_die)
	{
		data->someone_died = true;
		print_death(philo, now);
		pthread_mutex_unlock(&data->death_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (false);
}

static void	check_philo_eaten(t_data *data, int i, int *full)
{
	pthread_mutex_lock(&data->meals_eaten_mutex);
	if (data->philo[i].meals_eaten >= data->nb_must_eat)
		(*full)++;
	pthread_mutex_unlock(&data->meals_eaten_mutex);
}

void	*monitor(void *arg)
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
			if (philo_is_dead(&philo[i]))
				return (NULL);
			if (data->nb_must_eat > 0)
				check_philo_eaten(data, i, &full);
			i++;
		}
		if (full == data->nb_philo)
			return (declare_sim_over(data));
		usleep(100);
	}
	return (NULL);
}
