/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:35:10 by lserghin          #+#    #+#             */
/*   Updated: 2025/08/01 16:36:11 by lserghin         ###   ########.fr       */
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

typedef struct s_data
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
	pthread_mutex_t	meal;
	pthread_t		monitor;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				right_fork;
	int				left_fork;
	long			meal_counter;
	long			last_meal;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

void	ft_print_status(t_philo *philo, char *status);
void	ft_usleep(long duration_ms, t_data *data);
void	*ft_monitor_routine(void *arg);
void	ft_putstr_fd(char *s, int fd);
void	*ft_philo_routine(void *arg);

int		ft_init_data(t_data *data, int argc, char **argv);
int		ft_simulation_ended(t_data *data);
int		ft_atoi(const char *str);
int		ft_isnumber(char *str);

long	ft_gettime(void);

#endif
