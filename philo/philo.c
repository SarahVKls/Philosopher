/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaas <sklaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:55:24 by sklaas            #+#    #+#             */
/*   Updated: 2025/07/07 21:48:01 by sklaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	print_meals_summary(t_data *data)
// {
// 	int	i;

// 	printf("\n=== Meals Summary ===\n");
// 	i = -1;
// 	while (++i < data->nb_philo)
// 	{
// 		printf("Philosopher %d ate %d time%s\n",
// 			data->philo[i].id,
// 			data->philo[i].meals_eaten,
// 			data->philo[i].meals_eaten == 1 ? "" : "s");
// 	}
// }

void	destroy_all(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data->forks);
	free(philo);
	free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
		return (printf("ERROR : invalidnumber of args\n"), -1);
	if (!check_args(argv))
		return (printf("ERROR : invalid args\n"), -1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	philo = malloc(sizeof(t_philo) * ft_atol(argv[1]));
	if (!philo)
		return (1);
	init_all(data, philo, argv, argc);
	data->start_time = get_time();
	create_threads(data, philo);
	destroy_all(data, philo);
	return (0);
}
