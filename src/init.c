/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: co-neill <co-neill@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 07:02:16 by co-neill          #+#    #+#             */
/*   Updated: 2024/05/12 16:23:57 by co-neill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	init_args(t_context *context, char **av)
{
	context->philos_number = ft_atoi(av[1]);
	context->time_to_die = ft_atoi(av[2]);
	context->time_to_eat = ft_atoi(av[3]);
	context->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		context->required_meals = ft_atoi(av[5]);
	else
		context->required_meals = -1;
}

static void	init_philosophers(t_context *context)
{
	unsigned int	i;

	i = 0;
	while (i < context->philos_number)
	{
		context->philos[i].id = i + 1;
		context->philos[i].eating = 0;
		context->philos[i].meals_eaten = 0;
		context->philos[i].start_time = get_time_ms();
		context->philos[i].last_meal = get_time_ms();
		context->philos[i].dead = &context->death;
		context->philos[i].philos_number = &context->philos_number;
		context->philos[i].time_to_die = &context->time_to_die;
		context->philos[i].time_to_eat = &context->time_to_eat;
		context->philos[i].time_to_sleep = &context->time_to_sleep;
		context->philos[i].required_meals = &context->required_meals;
		context->philos[i].write_lock = &context->write_lock;
		context->philos[i].meal_lock = &context->meal_lock;
		context->philos[i].dead_lock = &context->dead_lock;
		context->philos[i].left_fork = &context->forks[i];
		if (!i)
			context->philos[i].right_fork = &context->forks[context->philos_number - 1];
		else
			context->philos[i].right_fork = &context->forks[i - 1];
		i++;
	}
}

static void	init_forks(t_context *context)
{
	unsigned int	i;

	i = 0;
	while (++i < context->philos_number)
	{
		pthread_mutex_init(&context->forks[i], NULL);
		i++;
	}
}

void	init_context(t_context *context, char **av)
{
	context->death = false;
	init_args(context, av);
	init_forks(context);
	init_philosophers(context);
	pthread_mutex_init(&context->write_lock, NULL);
	pthread_mutex_init(&context->meal_lock, NULL);
	pthread_mutex_init(&context->dead_lock, NULL);
}
