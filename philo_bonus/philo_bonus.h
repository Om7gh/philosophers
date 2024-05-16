/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:32:20 by omghazi           #+#    #+#             */
/*   Updated: 2024/05/10 11:20:53 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <limits.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/time.h>

#define RED "\e[1;31m"
#define NC "\e[0m"

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

struct s_philo
{
	size_t	last_meals;
	int		id;
	int		eating_meals;
	sem_t	*sem_philo;
	pid_t	process_id;
	t_table	*table;
} ;

struct s_table
{
	pthread_t	death_thread;
	sem_t		*sem_console;
	sem_t		*sem_finished;
	sem_t		*sem_forks;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		time_to_die;
	size_t		start_time;
	int			meals_nbr;
	int			philos_nbr;
} ;

void		ft_putnbr(int n);
void		ft_putstr(char *s);
int			start_simulation(t_philo *philo);
long		ft_atoi(char *s);
char		*ft_itoa(int n);
char		*ft_strdup(const char *s1);
size_t		ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
int			last_args(int av);
int			middle_args(int av);
int			first_args(int av);
int			parse_input(char **av, int ac);
int			process_begin(t_philo **philos, t_table *table);
void		*wait_death(void *p);
int			stop_process(t_philo **philo, t_table *table);
int			wait_process(t_philo **philo, t_table *table);
void		*check_death(void *p);
void		unlock_forks(t_philo *philo);
int			take_a_fork(t_philo *philo);
void		print(t_philo *philo, char *s);
void		ft_ussleep(size_t milliseconds);
size_t		get_current_time(void);
int			create_philos(t_philo **philo, t_table *table);
int			init_table(t_philo **philo, t_table *table, char **av);
