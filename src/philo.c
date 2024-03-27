/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: co-neill <co-neill@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:24:18 by co-neill          #+#    #+#             */
/*   Updated: 2024/03/28 08:41:43 by co-neill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	error(char *message)
{
	write(2, message, ft_strlen(message));
	exit(1);
}

static int	arg_isnumber(char *arg)
{
	while (*arg)
	{
		if (*arg < 48 || *arg > 57)
			return (0);
		arg++;
	}
	return (1);
}

static int	all_args_valid(char **av)
{
	if (!arg_isnumber(av[1]) || ft_atoi(av[1]) <= 0
		|| ft_atoi(av[1]) > PHILO_MAX)
		return (error("Philo number bad\n"), 0);
	if (!arg_isnumber(av[2]) || ft_atoi(av[2]) <= 0)
		return (error("Death time bad\n"), 0);
	if (!arg_isnumber(av[3]) || ft_atoi(av[3]) <= 0)
		return (error("Eat time bad\n"), 0);
	if (!arg_isnumber(av[4]) || ft_atoi(av[4]) <= 0)
		return (error("Sleep time bad\n"), 0);
	if (av[5] && (!arg_isnumber(av[5]) || ft_atoi(av[5]) <= 0))
		return (error("Meals to eat bad\n"), 0);
	return (1);
}

int	main(int ac, char **av)
{
	//t_context	context;
	
	if (ac != 5 && ac != 6)
		error("Incorrect number of args\n");
	if (!all_args_valid(av))
		error("Args must be positive integers\n");
}
