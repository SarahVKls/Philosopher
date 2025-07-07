/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaas <sklaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:56:55 by sklaas            #+#    #+#             */
/*   Updated: 2025/07/07 04:08:30 by sklaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		usleep(1000);
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
}

void	*one_philo(t_philo *philo)
{
	long	start;

	start = get_time();
	pthread_mutex_lock(&philo->left_fork[0]);
	printf("0 Philosopher %d has taken a fork\n", philo->id);
	ft_usleep(philo->data->time_to_die, philo->data);
	printf("%ld Philosopher %d died\n",
		get_time() - start, philo->id);
	pthread_mutex_unlock(&philo->left_fork[0]);
	return (NULL);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	check_simulation_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philo == 1)
		return (one_philo(philo), NULL);
	while (1)
	{
		if (check_simulation_end(philo))
			break ;
		take_forks(philo);
		print_action(philo, "is eating");
		pthread_mutex_lock(&philo->meal_mutex);
		philo->time_last_meal = get_time();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_mutex);
		ft_usleep(philo->data->time_to_eat, philo->data);
		unlock_forks(philo);
		print_action(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep, philo->data);
		print_action(philo, "is thinking");
		usleep(100);
	}
	return (NULL);
}
