/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:51:14 by omghazi           #+#    #+#             */
/*   Updated: 2024/04/27 16:25:08 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>

#define NC "\e[0m"
#define RED "\e[1;31m"

/* STRUCT */
typedef struct s_prog	t_prog;

typedef struct s_philo
{
	pthread_mutex_t		*left_fork; // one philo can hold a left fork in a time
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*write_lock; // to prevent data race in printing data
	pthread_mutex_t		*dead_lock; // to prevend data race if dying
	pthread_mutex_t		*meal_lock; // to prevent data race when eating a meal
	pthread_t			*thread_id;
	int					id;
	int					num_of_philos;
	int					*dead;
	size_t				time_to_eat; // time spend eating
	size_t				time_to_die; // time left for dying
	size_t				time_to_sleep;
	size_t				last_meal; // store the time of last meal of a thread
	size_t				meals_qty; // number of meals
	size_t				meals_eaten;
	t_prog				*data;
}	t_philo;

struct s_prog
{
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		*forks;
	int					dead;
	size_t				start_time;
	t_philo				*philos;
} ;

/* FUNCTIONS */
void	mr_propre(t_prog *init);
void	print(t_philo *philo, char *s);
int		death(t_prog *is_death);
void	is_dead(t_philo *dinner);
void	is_think(t_philo *dinner);
void	is_sleep(t_philo *dinner);
void	is_eat(t_philo *dinner);
void	is_dead(t_philo *dinner);
void	*monitoring(void *monitor);
void	*dinner_simulation(void *dinner);
int		dining(t_prog *dinner);
int		start_routine(t_prog *dinner);
int		ft_ussleep(size_t milisecond);
size_t	get_current_time(void);
t_prog	*life_cycle_init(t_philo *philo);
t_philo	*philos_data_init(char **av);
void	*my_malloc(size_t byte);
void	error(char *s);
int		first_args(int av);
int		middle_args(int av);
int		last_args(int av);
int		parse_input(char **av, int ac);
long	ft_atoi(char *s);