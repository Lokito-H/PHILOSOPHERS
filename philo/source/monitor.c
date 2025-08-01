/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:33:20 by lserghin          #+#    #+#             */
/*   Updated: 2025/08/01 16:16:00 by lserghin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_death(t_data *data)
{
	t_philo	*philo_ptr;

	philo_ptr = data->philos;
	while (philo_ptr < data->philos + data->num_of_philos)
	{
		pthread_mutex_lock(&data->meal);
		if (ft_gettime() - philo_ptr->last_meal >= data->time_to_die)
		{
			ft_print_status(philo_ptr, "died");
			pthread_mutex_lock(&data->ending);
			data->end_simulation = 1;
			pthread_mutex_unlock(&data->ending);
			return (pthread_mutex_unlock(&data->meal), 0);
		}
		pthread_mutex_unlock(&data->meal);
		philo_ptr++;
	}
	return (1);
}

static int	ft_check_meals(t_data *data)
{
	t_philo	*philo_ptr;
	int		full_philos;

	if (data->must_eat == -1)
		return (1);
	philo_ptr = data->philos;
	full_philos = 0;
	while (philo_ptr < data->philos + data->num_of_philos)
	{
		pthread_mutex_lock(&data->meal);
		if (philo_ptr->meal_counter >= data->must_eat)
			full_philos++;
		pthread_mutex_unlock(&data->meal);
		philo_ptr++;
	}
	if (full_philos == data->num_of_philos)
	{
		pthread_mutex_lock(&data->ending);
		data->end_simulation = 1;
		pthread_mutex_unlock(&data->ending);
		return (0);
	}
	return (1);
}

void	*ft_monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1337)
	{
		if (ft_simulation_ended(data))
			break ;
		if (!ft_check_death(data) || !ft_check_meals(data))
			break ;
		usleep(500);
	}
	return (NULL);
}
