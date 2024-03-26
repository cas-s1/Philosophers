/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: co-neill <co-neill@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:24:18 by co-neill          #+#    #+#             */
/*   Updated: 2024/03/27 10:54:06 by co-neill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	error(char *message)
{
	write(2, message, ft_strlen(message));
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

}

int	main(int ac, char **av)
{
	t_context	context;
}
