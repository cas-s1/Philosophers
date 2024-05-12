/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: co-neill <co-neill@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:17:28 by co-neill          #+#    #+#             */
/*   Updated: 2024/05/12 18:02:05 by co-neill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_dead_flag(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == true)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

static void	*philo_actions(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *) ptr;
	if (philo->id % 2 == 0)
		msleep(1);
	while (!check_dead_flag(philo))
	{
		devour(philo);
		slumber(philo);
		ponder(philo);
	}
	return (ptr);
}

int	create_threads(t_context *context)
{
	pthread_t		god;
	int				i;

	if (pthread_create(&god, NULL, &observe, context->philos))
		clean_and_exit("thread creation bad\n", context, 1);
	i = 0;
	while (i < context->philos_number)
	{
		if (pthread_create(&context->philos[i].thread, NULL, \
					&philo_actions, &context->philos[i]))
			clean_and_exit("thread creation bad\n", context, 1);
		i++;
	}
	i = 0;
	if (pthread_join(god, NULL))
		clean_and_exit("thread join bad\n", context, 1);
	while (i < context->philos_number)
	{
		if (pthread_join(context->philos[i].thread, NULL))
			clean_and_exit("thread join bad\n", context, 1);
		i++;
	}
	return (0);
}
