/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:32:55 by lserghin          #+#    #+#             */
/*   Updated: 2025/05/19 22:38:45 by lserghin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_cleanup(t_table *data)
{
	pthread_mutex_t	*current_fork;

	current_fork = data->forks;
	while (current_fork < data->forks + data->num_of_philos)
		pthread_mutex_destroy(current_fork++);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->ending);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	return ;
}

static int	ft_check_input(int argc, char **argv)
{
	int	index;

	if (argc != 5 && argc != 6)
	{
		printf("Usage\n./philo n_philos t_die t_eat t_sleep [must_eat].\n");
		return (0);
	}
	index = 1;
	while (index < argc)
	{
		if (!ft_isnumber(*(argv + index)))
		{
			printf("Error\nArgument %d must contain only digits.\n", index);
			return (0);
		}
		if (ft_atoi(*(argv + index)) <= 0)
		{
			printf("Error\nArgument %d must be a positive number.\n", index);
			return (0);
		}
		index++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	data;
	t_philo	*philo;

	if (!ft_check_input(argc, argv) || !ft_init_data(&data, argc, argv))
		return (1);
	philo = data.philos;
	while (philo < data.philos + data.num_of_philos)
	{
		if (pthread_create(&philo->thread, NULL, ft_philo_routine, philo))
			return (1);
		philo++;
	}
	if (pthread_create(&data.monitor, NULL, ft_monitor_routine, &data))
		return (printf("Error\nFailed to create monitor thread"), 1);
	philo = data.philos;
	while (philo < data.philos + data.num_of_philos)
	{
		if (pthread_join(philo->thread, NULL))
			return (1);
		philo++;
	}
	if (pthread_join(data.monitor, NULL))
		return (printf("Error\nFailed to join monitor thread"), 1);
	ft_cleanup(&data);
	return (0);
}
