/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:56:05 by lserghin          #+#    #+#             */
/*   Updated: 2025/08/05 19:10:03 by lserghin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_isnumber(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (!(*str >= 48 && *str <= 57))
			return (0);
		str++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	num;

	num = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return (-1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + (*str++ - '0');
		if ((num == INT_MAX / 10) && ((*str - '0') > INT_MAX % 10))
			return (-1);
	}
	return (num);
}

long	ft_gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(long duration_ms)
{
	long	start;

	start = ft_gettime();
	while (ft_gettime() - start <= duration_ms)
		usleep(500);
	return ;
}

void	ft_print_status(t_philo *philo, char *status)
{
	long	time;

	sem_wait(philo->data->print);
	time = ft_gettime() - philo->data->start_simulation;
	printf("%ld\t%d\t%s\n", time, philo->id, status);
	if (*status != 'd')
		sem_post(philo->data->print);
	return ;
}

int	ft_simulation_ended(t_data *data)
{
	int	is_ended;

	is_ended = 0;
	sem_wait(data->ending);
	if (data->end_simulation)
		is_ended = 1;
	sem_post(data->ending);
	return (is_ended);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
	return ;
}
