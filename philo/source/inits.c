/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:33:22 by lserghin          #+#    #+#             */
/*   Updated: 2025/05/19 00:04:52 by lserghin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_init_mutexes(t_table *data)
{
	pthread_mutex_t	*current_fork;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->forks)
		return (0);
	current_fork = data->forks;
	while (current_fork < data->forks + data->num_of_philos)
	{
		if (pthread_mutex_init(current_fork, NULL))
			return (0);
		current_fork++;
	}
	if (pthread_mutex_init(&data->print, NULL))
		return (0);
	if (pthread_mutex_init(&data->ending, NULL))
		return (0);
	return (1);
}

static int	ft_init_philos(t_table *data)
{
	t_philo	*current_philo;
	int		pos;

	data->philos = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philos)
		return (0);
	current_philo = data->philos;
	pos = 0;
	while (current_philo < data->philos + data->num_of_philos)
	{
		current_philo->id = pos + 1;
		current_philo->right_fork = pos;
		current_philo->left_fork = (pos + 1) % data->num_of_philos;
		if (!(current_philo->id % 2))
		{
			current_philo->left_fork = pos;
			current_philo->right_fork = (pos + 1) % data->num_of_philos;
		}
		current_philo->meal_counter = 0;
		current_philo->last_meal = ft_get_time();
		current_philo->data = data;
		current_philo++;
		pos++;
	}
	return (1);
}

int	ft_init_data(t_table *data, int argc, char **argv)
{
	data->num_of_philos = ft_atoi(*(argv + 1));
	data->time_to_die = ft_atoi(*(argv + 2));
	data->time_to_eat = ft_atoi(*(argv + 3));
	data->time_to_sleep = ft_atoi(*(argv + 4));
	data->must_eat = -1;
	if (argc == 6)
		data->must_eat = ft_atoi(*(argv + 5));
	data->start_simulation = ft_get_time();
	data->end_simulation = 0;
	if (!ft_init_philos(data) || !ft_init_mutexes(data))
	{
		printf("Error\nFailed to initialize data.");
		return (0);
	}
	return (1);
}
