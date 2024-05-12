/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: co-neill <co-neill@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:10:00 by co-neill          #+#    #+#             */
/*   Updated: 2024/05/12 15:59:11 by co-neill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	philosopher_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_time_ms() - philo->last_meal >= *philo->time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

static int	check_dead(t_philo *philos)
{
	unsigned int	i;

	i = 0;
	while (i < *philos[0].philos_number)
	{
		if (philosopher_dead(&philos[i]))
		{
			display_status(&philos[i], "died");
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_all_ate(t_philo *philos)
{
	unsigned int	finished;
	unsigned int	i;

	finished = 0;
	i = 0;
	if (*philos[0].required_meals == -1)
		return (0);
	while (i < *philos[0].philos_number)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= *philos[i].required_meals)
			finished++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (finished == *philos[0].philos_number)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*observe(void *ptr)
{
	t_philo	*philos;

	philos = (t_philo *) ptr;
	while (1)
		if (check_dead(philos) == 1 || check_all_ate(philos) == 1)
			break ;
	return (ptr);
}
