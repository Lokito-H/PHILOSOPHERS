/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:33:24 by lserghin          #+#    #+#             */
/*   Updated: 2025/05/19 22:43:50 by lserghin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_sleeping_thinking(t_philo *philo)
{
	ft_print_status(philo, "is sleeping");
	ft_safe_usleep(philo->data->time_to_sleep, philo->data);
	ft_print_status(philo, "is thinking");
	return ;
}

static void	ft_dropping_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_unlock(philo->data->forks + philo->right_fork);
		pthread_mutex_unlock(philo->data->forks + philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->data->forks + philo->left_fork);
		pthread_mutex_unlock(philo->data->forks + philo->right_fork);
	}
	return ;
}

static void	ft_eating(t_philo *philo)
{
	ft_print_status(philo, "is eating");
	philo->last_meal = ft_get_time();
	philo->meal_counter++;
	ft_safe_usleep(philo->data->time_to_eat, philo->data);
	return ;
}

static void	ft_taking_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->data->forks + philo->right_fork);
		ft_print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->data->forks + philo->left_fork);
		ft_print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->data->forks + philo->left_fork);
		ft_print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->data->forks + philo->right_fork);
		ft_print_status(philo, "has taken a fork");
	}
	return ;
}

void	*ft_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_of_philos == 1)
	{
		ft_print_status(philo, "has taken a fork");
		ft_safe_usleep(philo->data->time_to_die, philo->data);
		return (NULL);
	}
	if (philo->id % 2)
		ft_safe_usleep(1, philo->data);
	while (!philo->data->end_simulation)
	{
		ft_taking_forks(philo);
		ft_eating(philo);
		ft_dropping_forks(philo);
		ft_sleeping_thinking(philo);
	}
	return (NULL);
}
