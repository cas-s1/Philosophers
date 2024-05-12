/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: co-neill <co-neill@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:11:08 by co-neill          #+#    #+#             */
/*   Updated: 2024/05/12 17:54:54 by co-neill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <time.h>

# define PHILO_MAX 250

typedef struct s_philo
{
	pthread_t		thread;
	bool			*dead;
	int				id;
	int				eating;
	int				meals_eaten;
	int				last_meal;
	unsigned int	start_time;
	int				*philos_number;
	unsigned int	*time_to_die;
	unsigned int	*time_to_eat;
	unsigned int	*time_to_sleep;
	int				*required_meals;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philo;

typedef struct s_context
{
	t_philo			*philos;
	int				philos_number;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				required_meals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	dead_lock;
	bool			death;
}	t_context;

// init.c
void			init_context(t_context *context, char **av);

// philo.c
void			clean_and_exit(char *message, t_context *context, int code);

// actions.c
void			display_status(t_philo *philo, char *status);
void			ponder(t_philo *philo);
void			slumber(t_philo *philo);
void			devour(t_philo *philo);

// utils.c
int				ft_strlen(const char *str);
int				ft_atoi(const char *str);
unsigned int	get_time_ms(void);
void			msleep(unsigned int milliseconds);
void			destroy_mutexes(t_context *context);

// threads.c
int				check_dead_flag(t_philo *philo);
int				create_threads(t_context *context);

// observe.c
void			*observe(void *ptr);

#endif
