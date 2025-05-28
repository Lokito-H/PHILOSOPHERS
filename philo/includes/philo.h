/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:35:10 by lserghin          #+#    #+#             */
/*   Updated: 2025/05/27 17:22:22 by lserghin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>

typedef struct s_philo	t_philo;

typedef struct s_table
{
	long			num_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat;
	long			start_simulation;
	int				end_simulation;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	ending;
	pthread_t		monitor;
}	t_table;

typedef struct s_philo
{
	int				id;
	int				right_fork;
	int				left_fork;
	long			meal_counter;
	long			last_meal;
	pthread_t		thread;
	t_table			*data;
}	t_philo;

int		ft_init_data(t_table *data, int argc, char **argv);
void	ft_safe_usleep(long duration_ms, t_table *data);
void	ft_print_status(t_philo *philo, char *status);
int		ft_atoi(const char *str);
int		ft_isnumber(char *str);
long	ft_get_time(void);

void	*ft_monitor_routine(void *arg);
void	*ft_philo_routine(void *arg);

#endif
