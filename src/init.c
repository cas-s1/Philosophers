/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: co-neill <co-neill@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 07:02:16 by co-neill          #+#    #+#             */
/*   Updated: 2024/05/12 18:01:36 by co-neill         ###   ########.fr       */
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

static void	init_philosophers(t_context *c)
{
	int	i;

	i = -1;
	while (++i < c->philos_number)
	{
		c->philos[i].id = i + 1;
		c->philos[i].eating = 0;
		c->philos[i].meals_eaten = 0;
		c->philos[i].start_time = get_time_ms();
		c->philos[i].last_meal = get_time_ms();
		c->philos[i].dead = &c->death;
		c->philos[i].philos_number = &c->philos_number;
		c->philos[i].time_to_die = &c->time_to_die;
		c->philos[i].time_to_eat = &c->time_to_eat;
		c->philos[i].time_to_sleep = &c->time_to_sleep;
		c->philos[i].required_meals = &c->required_meals;
		c->philos[i].write_lock = &c->write_lock;
		c->philos[i].meal_lock = &c->meal_lock;
		c->philos[i].dead_lock = &c->dead_lock;
		c->philos[i].left_fork = &c->forks[i];
		if (!i)
			c->philos[i].right_fork = &c->forks[c->philos_number - 1];
		else
			c->philos[i].right_fork = &c->forks[i - 1];
	}
}

static void	init_forks(t_context *context)
{
	int	i;

	i = 0;
	while (i < context->philos_number)
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
