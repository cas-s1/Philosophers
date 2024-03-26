/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: co-neill <co-neill@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:11:08 by co-neill          #+#    #+#             */
/*   Updated: 2024/03/27 10:51:42 by co-neill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define PHILO_MAX 500

# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <time.h>

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
}	t_philo;

typedef struct s_context
{
	t_philo	*philos;
}	t_context;

// philo.c
void	error(char *message);

// utils.c
int	ft_strlen(const char *str);
int	ft_atoi(const char *str);

#endif
