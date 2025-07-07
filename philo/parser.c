/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaas <sklaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 00:30:18 by sklaas            #+#    #+#             */
/*   Updated: 2025/07/07 05:39:27 by sklaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_valid_arg(char *str)
{
	int	j;

	if (str[0] == '\0')
		return (0);
	j = 0;
	if (str[j] == '+')
	{
		if (str[j + 1] == '+')
			return (0);
		j++;
	}
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
			return (0);
		j++;
	}
	return (1);
}

int	check_args(char **argv)
{
	int		i;
	long	val;

	i = 1;
	if (ft_atol(argv[1]) > 200)
		return (0);
	while (argv[i])
	{
		if (!is_valid_arg(argv[i]))
			return (0);
		val = ft_atol(argv[i]);
		if (val < 0 || val > INT_MAX)
			return (0);
		i++;
	}
	if ((ft_atol(argv[3]) < 1) || (ft_atol(argv[1]) < 1))
		return (0);
	return (1);
}
