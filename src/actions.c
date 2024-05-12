/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: co-neill <co-neill@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:48:00 by co-neill          #+#    #+#             */
/*   Updated: 2024/05/12 18:01:45 by co-neill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	display_status(t_philo *philo, char *status)
{
	unsigned int	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_time_ms() - philo->start_time;
	if (!check_dead_flag(philo))
		printf("%d %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(philo->write_lock);
}

void	ponder(t_philo *philo)
{
	display_status(philo, "is thinking");
}

void	slumber(t_philo *philo)
{
	display_status(philo, "is sleeping");
	msleep(*philo->time_to_sleep);
}

void	devour( t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	display_status(philo, "has taken a fork");
	if (*philo->philos_number == 1)
	{
		msleep(*philo->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	display_status(philo, "has taken a fork");
	philo->eating = 1;
	display_status(philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	msleep(*philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
