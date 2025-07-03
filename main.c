/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaas <sklaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:55:24 by sklaas            #+#    #+#             */
/*   Updated: 2025/07/03 01:50:14 by sklaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_data(t_data *data, t_philo *philo, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->nb_must_eat = ft_atoi(argv[5]);
	//init philo
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc < 5 || argc > 6)
		return (0);
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isalpha(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	if (ft_atoi(argv[3]) < 1)
		return (0);
	if (ft_atoi(argv[1]) < 1)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	int		i;
	t_data	*data;
	t_philo	*philo;

	i = 0;
	if (!check_args(argc, argv))
		return (printf("ERROR : invalid args\n"), -1);
	init_data(data, philo, argv);
	create_thread();
	return (0);
}
