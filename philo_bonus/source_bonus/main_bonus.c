/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:55:17 by lserghin          #+#    #+#             */
/*   Updated: 2025/05/27 17:29:26 by lserghin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_cleanup(t_table *data)
{
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->ending);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_ENDING);
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
	t_philo *current_philo;
	int		status;
	
	if (!ft_check_input(argc, argv) || !ft_init_data(&data, argc, argv))
		return (1);
	current_philo = data.philos;
	while (current_philo < data.philos + data.num_of_philos)
	{
		current_philo->pid = fork();
		if (!current_philo->pid)
			ft_philo_routine(current_philo);
		else if(current_philo->pid < 0)
			return (printf("Error\nFork failed\n"), 1);
		current_philo++;
	}
	waitpid(-1, &status, 0);
	current_philo = data.philos;
	while (current_philo < data.philos + data.num_of_philos)
		waitpid(current_philo++->pid, NULL, 0);
	current_philo = data.philos;
	while (current_philo < data.philos + data.num_of_philos)
		kill(current_philo++->pid, SIGKILL);
	return (ft_cleanup(&data), 0);
}
