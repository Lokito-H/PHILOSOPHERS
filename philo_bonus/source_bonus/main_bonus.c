/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:55:17 by lserghin          #+#    #+#             */
/*   Updated: 2025/08/01 17:10:30 by lserghin         ###   ########.fr       */
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
	char	**argv_ptr;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Usage\n./philo n_philos t_die t_eat t_sleep [m_eat].\n", 2);
		return (0);
	}
	argv_ptr = argv + 1;
	while (argv_ptr < argv + argc)
	{
		if (!ft_isnumber(*argv_ptr))
		{
			ft_putstr_fd("Error\n", 2);
			ft_putstr_fd(*argv_ptr, 2);
			return (ft_putstr_fd(" must contain only digits.\n", 2), 0);
		}
		if (ft_atoi(*argv_ptr) <= 0)
		{
			ft_putstr_fd("Error\n", 2);
			ft_putstr_fd(*argv_ptr, 2);
			return (ft_putstr_fd(" must be a positive number.\n", 2), 0);
		}
		argv_ptr++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	data;
	t_philo *philo_ptr;
	pid_t	*pid_ptr;
	int		status;
	
	if (!ft_check_input(argc, argv) || !ft_init_data(&data, argc, argv))
		return (1);
	philo_ptr = data.philos;
	pid_ptr = philo_ptr->pid
	while (philo_ptr < data.philos + data.num_of_philos)
	{
		*pid_ptr = fork();
		if (!*pid_ptr)
			ft_philo_routine(philo_ptr);
		else if(*pid_ptr < 0)
			return (printf("Error\nFork failed\n"), 1);
		philo_ptr++;
		pid_ptr++;
	}
	waitpid(-1, &status, 0);
	philo_ptr = data.philos;
	while (philo_ptr < data.philos + data.num_of_philos)
		waitpid(philo_ptr++->pid, NULL, 0);
	philo_ptr = data.philos;
	while (philo_ptr < data.philos + data.num_of_philos)
		kill(philo_ptr++->pid, SIGKILL);
	return (ft_cleanup(&data), 0);
}
