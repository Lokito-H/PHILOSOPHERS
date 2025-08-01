/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:55:29 by lserghin          #+#    #+#             */
/*   Updated: 2025/08/01 16:04:42 by lserghin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_philo_routine(t_philo *philo)
{
	sem_t	*sem_forks = sem_open(SEM_FORKS, 0);
	sem_t	*sem_print = sem_open(SEM_PRINT, 0);
	// sem_t	*sem_ending = sem_open(SEM_ENDING, 0);
	while (1337)
	{
		sem_wait(sem_forks);
		ft_print_status(philo, "has taken a fork");
		ft_print_status(philo, "has taken a fork");
		sem_wait(sem_forks);
		ft_print_status(philo, "is eating");
		philo->last_meal = ft_get_time();
		philo->meal_counter++;
		usleep(philo->data->time_to_eat * 1000);
		sem_post(sem_forks);
		sem_post(sem_forks);
		ft_print_status(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		ft_print_status(philo, "is thinking");
	}
	sem_close(sem_forks);
	sem_close(sem_print);
	exit(0);
	return ;
}
