/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:52:40 by lserghin          #+#    #+#             */
/*   Updated: 2025/05/24 20:52:08 by lserghin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

# define SEM_FORKS "/sem_forks"
# define SEM_PRINT "/sem_print"
# define SEM_ENDING "/sem_ending"

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
	pid_t			*pids;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*ending;
	pthread_t		monitor;
}	t_table;

typedef struct s_philo
{
	int				id;
	long			meal_counter;
	long			last_meal;
	pid_t			pid;
	pthread_t		t;
	t_table			*data;
}	t_philo;

int		ft_init_data(t_table *data, int argc, char **argv);
void	ft_safe_usleep(long duration_ms, t_table *data);
void	ft_print_status(t_philo *philo, char *status);
int		ft_atoi(const char *str);
int		ft_isnumber(char *str);
long	ft_get_time(void);

void	ft_philo_routine(t_philo *philo);
void	*ft_monitor_routine(void *arg);

#endif