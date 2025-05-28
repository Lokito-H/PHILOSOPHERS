/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:55:52 by lserghin          #+#    #+#             */
/*   Updated: 2025/05/24 18:52:52 by lserghin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	if (!ft_init_philos(data))
	{
        printf("Error\nFailed to initialize data.");
		return (0);
	}
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
