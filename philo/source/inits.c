/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:33:22 by lserghin          #+#    #+#             */
/*   Updated: 2025/08/04 17:02:14 by lserghin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_init_mutexes(t_data *data)
{
	pthread_mutex_t	*fork_ptr;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->forks)
		return (0);
	fork_ptr = data->forks;
	while (fork_ptr < data->forks + data->num_of_philos)
	{
		if (pthread_mutex_init(fork_ptr, NULL))
			return (ft_cleanup(data, NULL), 0);
		fork_ptr++;
	}
	if (pthread_mutex_init(&data->print, NULL))
		return (0);
	if (pthread_mutex_init(&data->ending, NULL))
		return (0);
	if (pthread_mutex_init(&data->meal, NULL))
		return (0);
	return (1);
}

static int	ft_init_philos(t_data *data)
{
	t_philo	*philo_ptr;
	int		pos;

	data->philos = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philos)
		return (0);
	philo_ptr = data->philos;
	pos = 0;
	while (philo_ptr < data->philos + data->num_of_philos)
	{
		philo_ptr->id = pos + 1;
		philo_ptr->right_fork = pos;
		philo_ptr->left_fork = (pos + 1) % data->num_of_philos;
		philo_ptr->meal_counter = 0;
		philo_ptr->last_meal = ft_gettime();
		philo_ptr->data = data;
		philo_ptr++;
		pos++;
	}
	return (1);
}

int	ft_init_data(t_data *data, int argc, char **argv)
{
	data->num_of_philos = ft_atoi(*(argv + 1));
	data->time_to_die = ft_atoi(*(argv + 2));
	data->time_to_eat = ft_atoi(*(argv + 3));
	data->time_to_sleep = ft_atoi(*(argv + 4));
	data->must_eat = -1;
	if (argc == 6)
		data->must_eat = ft_atoi(*(argv + 5));
	data->start_simulation = ft_gettime();
	data->end_simulation = 0;
	if (!ft_init_philos(data) || !ft_init_mutexes(data))
	{
		ft_putstr_fd("Error\nFailed to initialize data\n", 2);
		return (0);
	}
	return (1);
}
