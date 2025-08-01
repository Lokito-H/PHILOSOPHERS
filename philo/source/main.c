/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:32:55 by lserghin          #+#    #+#             */
/*   Updated: 2025/08/01 16:10:42 by lserghin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_cleanup(t_data *data, t_philo *philo_fail)
{
	pthread_mutex_t	*fork_ptr;
	t_philo			*philo_ptr;

	pthread_mutex_lock(&data->ending);
	data->end_simulation = 1;
	pthread_mutex_unlock(&data->ending);
	if (philo_fail && data->philos)
	{
		philo_ptr = data->philos;
		while (philo_ptr < philo_fail)
			pthread_join((philo_ptr++)->thread, NULL);
	}
	if (data->forks)
	{
		fork_ptr = data->forks;
		while (fork_ptr < data->forks + data->num_of_philos)
			pthread_mutex_destroy(fork_ptr++);
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->ending);
	pthread_mutex_destroy(&data->meal);
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
	t_data	data;
	t_philo	*philo;

	memset(&data, 0, sizeof(t_data));
	if (!ft_check_input(argc, argv) || !ft_init_data(&data, argc, argv))
		return (1);
	philo = data.philos;
	while (philo < data.philos + data.num_of_philos)
	{
		if (pthread_create(&philo->thread, NULL, ft_philo_routine, philo))
			return (ft_cleanup(&data, philo), 1);
		philo++;
	}
	pthread_create(&data.monitor, NULL, ft_monitor_routine, &data);
	philo = data.philos;
	while (philo < data.philos + data.num_of_philos)
	{
		if (pthread_join(philo->thread, NULL))
			return (1);
		philo++;
	}
	if (pthread_join(data.monitor, NULL))
		return (1);
	return (ft_cleanup(&data, NULL), 0);
}
