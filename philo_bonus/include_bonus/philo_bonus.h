/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:52:40 by lserghin          #+#    #+#             */
/*   Updated: 2025/08/06 17:49:49 by marvin           ###   ########.fr       */
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

typedef struct s_data
{
	long			num_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat;
	long			start_simulation;
	t_philo			*philos;
	pid_t			*pids;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*ending;
}	t_data;

typedef struct s_philo
{
	int				id;
	long			meal_counter;
	long			last_meal;
	pid_t			pid;
	pthread_t		monitor;
	t_data			*data;
}	t_philo;

int		ft_init_data(t_data *data, int argc, char **argv);
int		ft_simulation_ended(t_data *data);
int		ft_atoi(const char *str);
int		ft_isnumber(char *str);

void	ft_print_status(t_philo *philo, char *status);
void	ft_philo_routine(t_philo *philo);
void	*ft_monitor_routine(void *arg);
void	ft_putstr_fd(char *s, int fd);
void	ft_usleep(long duration_ms);

long	ft_gettime(void);

#endif
