/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:34:14 by omghazi           #+#    #+#             */
/*   Updated: 2024/05/19 18:21:20 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("gettimeofday() error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static void	create_philo(t_philo *philos, int philos_num, int *i, char **av)
{
	(philos + *i)->num_of_philos = philos_num;
	(philos + *i)->id = *i + 1;
	(philos + *i)->meals_eaten = 0;
	(philos + *i)->time_to_eat = ft_atoi(av[3]);
	(philos + *i)->time_to_die = ft_atoi(av[2]);
	(philos + *i)->time_to_sleep = ft_atoi(av[4]);
	(philos + *i)->meals_qty = -1;
	if (ft_atoi(av[5]) >= 0)
		(philos + *i)->meals_qty = ft_atoi(av[5]);
	(philos + *i)->dead = 0;
	(philos + *i)->last_meal = get_current_time();
}

t_philo	*philos_data_init(char **av)
{
	t_philo	*philos;
	int		philos_num;
	int		i;

	philos_num = ft_atoi(av[1]);
	philos = (t_philo *)malloc(sizeof(t_philo) * philos_num);
	if (!philos)
		return (printf("error with malloc"), NULL);
	philos->thread_id = (pthread_t *)malloc(sizeof(pthread_t) * philos_num);
	if (!philos->thread_id)
		return (free(philos), philos = NULL, NULL);
	i = -1;
	while (++i < philos_num)
		create_philo(philos, philos_num, &i, av);
	return (philos);
}

static void	init_mutex(t_prog *init, int *i)
{
	pthread_mutex_init(&(init->forks[*i]), NULL);
	pthread_mutex_init(&(init->write_lock), NULL);
	pthread_mutex_init(&(init->dead_lock), NULL);
	pthread_mutex_init(&(init->meal_lock), NULL);
	init->philos[*i].write_lock = &(init->write_lock);
	init->philos[*i].dead_lock = &(init->dead_lock);
	init->philos[*i].meal_lock = &(init->meal_lock);
	init->philos[*i].dead = &(init->dead);
}

t_prog	*life_cycle_init(t_philo *philo)
{
	t_prog	*init;
	int		i;

	init = (t_prog *)malloc(sizeof(t_prog));
	if (!init)
		return (printf("error with malloc\n"), NULL);
	init->philos = philo;
	init->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
			init->philos->num_of_philos);
	if (!init->forks)
		return (free(init), init = NULL, printf("error with malloc\n"), NULL);
	i = -1;
	while (++i < init->philos->num_of_philos)
	{
		init_mutex(init, &i);
		if (i == 0)
			init->philos[i].left_fork = \
					&(init->forks[init->philos->num_of_philos - 1]);
		else
			init->philos[i].left_fork = &(init->forks[i - 1]);
		init->philos[i].right_fork = &(init->forks[i]);
		(init->philos + i)->data = init;
	}
	return (init);
}
