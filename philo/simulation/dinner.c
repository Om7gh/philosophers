/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 10:07:54 by omghazi           #+#    #+#             */
/*   Updated: 2024/05/09 23:45:45 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	*one_thread(void *data)
{
	t_philo	*philos;

	philos = (void *)data;
	print(philos, "has taken left fork");
	ft_ussleep(philos->time_to_die);
	print(philos, "died");
	return (NULL);
}

int	start_routine(t_prog *dinner)
{
	dinner->start_time = get_current_time();
	if (dinner->philos->meals_qty == 0)
		return (1);
	else if (dinner->philos->num_of_philos == 1)
	{
		if (pthread_create(&(dinner->philos->thread_id[0]), NULL, one_thread, \
				dinner->philos) != 0)
			return (printf("thread create error\n"), 0);
		if (pthread_join(dinner->philos->thread_id[0], NULL) != 0)
			return (printf("thread join error\n"), 0);
	}
	else if (dinner->philos->num_of_philos > 1)
		if (!dining(dinner))
			return (0);
	return (1);
}

int	dining(t_prog *dinner)
{
	pthread_t	thr;
	int			i;

	i = -1;
	while (++i < dinner->philos->num_of_philos)
	{
		if (pthread_create(&(dinner->philos->thread_id[i]), \
			NULL, dinner_simulation, dinner->philos + i) != 0)
			return (printf("thread create error\n"), 0);
	}
	if (pthread_create(&thr, NULL, \
			&monitoring, dinner) != 0)
		return (printf("thread create error\n"), 0);
	if (pthread_join(thr, NULL) != 0)
		return (printf("thread join error\n"), 0);
	i = -1;
	while (++i < dinner->philos->num_of_philos)
		if (pthread_join(dinner->philos->thread_id[i], NULL) != 0)
			return (printf("thread join error\n"), 0);
	return (1);
}

void	*dinner_simulation(void *dinner)
{
	t_philo	*start;
	int		i;

	i = -1;
	start = (t_philo *)dinner;
	if (start->id % 2 == 0)
		ft_ussleep(start->time_to_eat);
	while (!death(start->data))
	{
		is_eat(start);
		if (start->meals_eaten == start->meals_qty)
			break ;
		is_sleep(start);
		is_think(start);
	}
	return (NULL);
}

void	*monitoring(void *monitor)
{
	t_prog	*init;
	int		i;

	init = (t_prog *)monitor;
	while (1)
	{
		pthread_mutex_lock(&(init->meal_lock));
		pthread_mutex_lock(&(init->dead_lock));
		if (init->dead || init->philos->meals_eaten == init->philos->meals_qty)
		{
			pthread_mutex_unlock(&(init->dead_lock));
			pthread_mutex_unlock(&(init->meal_lock));
			break ;
		}
		pthread_mutex_unlock(&(init->dead_lock));
		pthread_mutex_unlock(&(init->meal_lock));
		i = -1;
		while (++i < init->philos->num_of_philos && !death(init))
			is_dead(init->philos + i);
	}
	return (NULL);
}
