/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:55:29 by lserghin          #+#    #+#             */
/*   Updated: 2025/08/06 17:49:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_eating(t_philo *philo)
{
	sem_wait(philo->data->forks);
	ft_print_status(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	ft_print_status(philo, "has taken a fork");
	sem_wait(philo->data->ending);
	ft_print_status(philo, "is eating");
	philo->last_meal = ft_gettime();
	philo->meal_counter++;
	sem_post(philo->data->ending);
	ft_usleep(philo->data->time_to_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	return ;
}

static void	ft_sleeping(t_philo *philo)
{
	ft_print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
	return ;
}

static void	ft_thinking(t_philo *philo)
{
	ft_print_status(philo, "is thinking");
	if (philo->data->num_of_philos % 2
		&& philo->data->time_to_eat >= philo->data->time_to_sleep)
		ft_usleep(philo->data->time_to_eat);
	return ;
}

void	ft_philo_routine(t_philo *philo)
{
	if (pthread_create(&philo->monitor, NULL, ft_monitor_routine, philo))
		return ((void)exit(1));
	if (philo->data->num_of_philos == 1)
	{
		sem_wait(philo->data->forks);
		ft_print_status(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die);
		ft_print_status(philo, "died");
		exit(1);
	}
	if (!(philo->id % 2))
		ft_usleep(1);
	while (1337)
	{
		ft_eating(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
	}
	if (pthread_join(philo->monitor, NULL))
		return ((void)exit(1));
	return ((void)exit(0));
}
