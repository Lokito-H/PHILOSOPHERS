/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:33:26 by lserghin          #+#    #+#             */
/*   Updated: 2025/05/19 21:38:09 by lserghin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "philo.h"

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

long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_safe_usleep(long duration_ms, t_table *data)
{
	long	start;
	long	elapsed;

	start = ft_get_time();
	while (1337)
	{
		pthread_mutex_lock(&data->ending);
		if (data->end_simulation)
		{
			pthread_mutex_unlock(&data->ending);
			break ;
		}
		pthread_mutex_unlock(&data->ending);
		elapsed = ft_get_time() - start;
		if (elapsed >= duration_ms)
			break ;
		usleep(100);
	}
	return ;
}

void	ft_print_status(t_philo *philo, char *status)
{
	long	time;

	pthread_mutex_lock(&philo->data->print);
	if (philo->data->end_simulation)
	{
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	time = ft_get_time() - philo->data->start_simulation;
	printf("%ld\t%d\t%s\n", time, philo->id, status);
	pthread_mutex_unlock(&philo->data->print);
	return ;
}
