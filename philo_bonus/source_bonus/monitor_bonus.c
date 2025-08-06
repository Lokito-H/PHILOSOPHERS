/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:55:46 by lserghin          #+#    #+#             */
/*   Updated: 2025/08/06 17:48:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1337)
	{
		sem_wait(philo->data->ending);
		if ((ft_gettime() - philo->last_meal) >= philo->data->time_to_die)
		{
			sem_post(philo->data->ending);
			ft_print_status(philo, "died");
			exit(1);
		}
		else if (philo->data->must_eat != -1
			&& philo->meal_counter >= philo->data->must_eat)
		{
			sem_post(philo->data->ending);
			exit (0);
		}
		sem_post(philo->data->ending);
		usleep(1000);
	}
	return (NULL);
}
