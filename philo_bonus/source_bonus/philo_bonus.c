/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:55:29 by lserghin          #+#    #+#             */
/*   Updated: 2025/08/05 20:05:40 by lserghin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_philo_routine(t_philo *philo)
{
	sem_t	*sem_forks = sem_open(SEM_FORKS, 0);
	sem_t	*sem_print = sem_open(SEM_PRINT, 0);
	sem_t	*sem_ending = sem_open(SEM_ENDING, 0);

	if (pthread_create(&philo->monitor, NULL, &ft_monitor_routine, philo))
	{
		ft_putstr_fd("Error: Could not create monitor thread.\n", 2);
		exit(1);
	}
	while (1337)
	{
		sem_wait(sem_forks);
		ft_print_status(philo, "has taken a fork");
		sem_wait(sem_forks);
		ft_print_status(philo, "has taken a fork");
		
		sem_wait(sem_ending);
		ft_print_status(philo, "is eating");
		philo->last_meal = ft_gettime();
		philo->meal_counter++;
		sem_post(sem_ending);
		
		ft_usleep(philo->data->time_to_eat);
		sem_post(sem_forks);
		sem_post(sem_forks);
		
		ft_print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		ft_print_status(philo, "is thinking");
		if (philo->data->num_of_philos % 2
			&& philo->data->time_to_eat >= philo->data->time_to_sleep)
			ft_usleep(philo->data->time_to_eat);
	}
	if (pthread_join(philo->monitor, NULL))
	{
		printf("Error joining thread\n");
		return ;
	}
	sem_close(sem_forks);
	sem_close(sem_print);
	return ((void)exit(0));
}
