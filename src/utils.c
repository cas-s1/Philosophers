/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: co-neill <co-neill@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:13:40 by co-neill          #+#    #+#             */
/*   Updated: 2024/05/12 17:55:34 by co-neill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while (*str == 32 || (*str > 8 && *str < 14))
		str++;
	if (*str == 45)
	{
		sign *= 1;
		str++;
	}
	else if (*str == 43)
		str++;
	while (*str > 47 && *str < 58)
	{
		res = res * 10 + *str - 48;
		str++;
	}
	return (res * sign);
}

unsigned int	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	msleep(unsigned int milliseconds)
{
	unsigned int	start;

	start = get_time_ms();
	while (get_time_ms() - start < milliseconds)
		usleep(100);
}

void	destroy_mutexes(t_context *context)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&context->write_lock);
	pthread_mutex_destroy(&context->meal_lock);
	pthread_mutex_destroy(&context->dead_lock);
	while (i < context->philos_number)
	{
		pthread_mutex_destroy(&context->forks[i]);
		i++;
	}
}
