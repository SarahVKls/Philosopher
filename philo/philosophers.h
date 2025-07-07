/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaas <sklaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:56:35 by sklaas            #+#    #+#             */
/*   Updated: 2025/07/07 21:07:19 by sklaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <threads.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

struct	s_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				nb_must_eat;
	long int		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meals_eaten_mutex;
	pthread_t		monitor_thread;
	bool			someone_died;
	struct s_philo	*philo;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	pthread_t		thread;
	int				id;
	long			time_last_meal;
	int				meals_eaten;
}	t_philo;

//Utils.c
long		ft_atol(const char *str);
int			ft_isdigit(int c);
long int	get_time(void);
void		ft_usleep(long duration, t_data *data);
void		print_action(t_philo *philo, char *msg);

//Routine.c
void		*routine(void *arg);

//Monitoring.c
void		*monitor(void *arg);

//Parser.c
int			check_args(char **argv);

//Init.c
void		init_all(t_data *data, t_philo *philo, char **argv, int argc);
void		*create_threads(t_data *data, t_philo *philo);

#endif
