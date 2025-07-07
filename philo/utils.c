/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaas <sklaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:52:22 by sklaas            #+#    #+#             */
/*   Updated: 2025/07/07 21:23:04 by sklaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atol(const char *str)
{
	int		i;
	long	result;
	int		sign;

	result = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	return (0);
}

long int	get_time(void)
{
	struct timeval	tv;
	long int		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long duration, t_data *data)
{
	long	start;
	long	now;

	start = get_time();
	while (1)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->someone_died)
		{
			pthread_mutex_unlock(&data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->death_mutex);
		now = get_time();
		if ((now - start) >= duration)
			break ;
		usleep(500);
	}
}

void	print_action(t_philo *philo, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->death_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->someone_died)
	{
		timestamp = get_time() - philo->data->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_unlock(&philo->data->death_mutex);
}
