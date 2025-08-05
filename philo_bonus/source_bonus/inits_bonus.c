/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:55:52 by lserghin          #+#    #+#             */
/*   Updated: 2025/08/05 19:16:53 by lserghin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_init_semaphores(t_data *data)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_ENDING);
	data->forks = sem_open(SEM_FORKS, O_CREAT, 0644, data->num_of_philos);
	data->print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	data->ending = sem_open(SEM_ENDING, O_CREAT, 0644, 1);
	if (!data->forks || !data->print || !data->ending)
		return (0);
	return (1);
}

static int	ft_init_philos(t_data *data)
{
	t_philo	*philo_ptr;
	int		pos;

	data->philos = malloc(sizeof(t_philo) * data->num_of_philos);
	data->pids = malloc(sizeof(pid_t) * data->num_of_philos);
	if (!data->philos || !data->pids)
		return (0);
	philo_ptr = data->philos;
	pos = 0;
	while (philo_ptr < data->philos + data->num_of_philos)
	{
		philo_ptr->id = pos + 1;
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
	if (!ft_init_philos(data) || !ft_init_semaphores(data))
	{
		ft_putstr_fd("Error\nFailed to initialize data.", 2);
		return (0);
	}
	return (1);
}
