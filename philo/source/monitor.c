/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:33:20 by lserghin          #+#    #+#             */
/*   Updated: 2025/05/19 21:42:28 by lserghin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_death(t_table *data)
{
	t_philo	*current_philo;

	current_philo = data->philos;
	while (current_philo < data->philos + data->num_of_philos)
	{
		pthread_mutex_lock(&data->ending);
		if (data->end_simulation)
		{
			pthread_mutex_unlock(&data->ending);
			return (0);
		}
		if (ft_get_time() - current_philo->last_meal >= data->time_to_die)
		{
			ft_print_status(current_philo, "died");
			data->end_simulation = 1;
			pthread_mutex_unlock(&data->ending);
			return (0);
		}
		pthread_mutex_unlock(&data->ending);
		current_philo++;
	}
	return (1);
}

static int	ft_check_meals(t_table *data)
{
	t_philo	*current_philo;
	int		full_philos;

	if (data->must_eat == -1)
		return (1);
	current_philo = data->philos;
	full_philos = 0;
	while (current_philo < data->philos + data->num_of_philos)
	{
		if (current_philo->meal_counter >= data->must_eat)
			full_philos++;
		current_philo++;
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
	t_table	*data;

	data = (t_table *)arg;
	while (1337)
	{
		if (!ft_check_meals(data) || !ft_check_death(data))
			break ;
		usleep(100);
	}
	return (NULL);
}
