/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:33:26 by lserghin          #+#    #+#             */
/*   Updated: 2025/08/06 17:47:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_simulation_ended(t_data *data)
{
	int	is_ended;

	is_ended = 0;
	pthread_mutex_lock(&data->ending);
	if (data->end_simulation)
		is_ended = 1;
	pthread_mutex_unlock(&data->ending);
	return (is_ended);
}

void	ft_usleep(long duration_ms, t_data *data)
{
	long	start;

	start = ft_gettime();
	while (ft_gettime() - start <= duration_ms)
	{
		if (ft_simulation_ended(data))
			break ;
		usleep(500);
	}
	return ;
}

void	ft_print_status(t_philo *philo, char *status)
{
	long	time;

	pthread_mutex_lock(&philo->data->print);
	if (!ft_simulation_ended(philo->data))
	{
		time = ft_gettime() - philo->data->start_simulation;
		printf("%ld\t%d\t%s\n", time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->print);
	return ;
}
