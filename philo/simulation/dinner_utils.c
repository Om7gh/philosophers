/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 10:09:30 by omghazi           #+#    #+#             */
/*   Updated: 2024/05/09 23:03:58 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	is_dead(t_philo *dinner)
{
	pthread_mutex_lock(&(dinner->data->dead_lock));
	pthread_mutex_lock(&(dinner->data->meal_lock));
	if ((get_current_time() - dinner->last_meal) > dinner->time_to_die \
			&& dinner->data->dead == 0)
	{
		dinner->data->dead = 1;
		pthread_mutex_lock(&(dinner->data->write_lock));
		printf("%ld\t%d\t%s\n", get_current_time() - dinner->data->start_time, \
				dinner->id, "died");
		pthread_mutex_unlock(&(dinner->data->write_lock));
	}
	pthread_mutex_unlock(&(dinner->data->dead_lock));
	pthread_mutex_unlock(&(dinner->data->meal_lock));
}

void	print(t_philo *philo, char *s)
{
	pthread_mutex_lock(&(philo->data->write_lock));
	if (!death(philo->data))
		printf("%ld\t%d\t%s\n", get_current_time() - \
				philo->data->start_time, philo->id, s);
	pthread_mutex_unlock(&(philo->data->write_lock));
}

void	is_eat(t_philo *dinner)
{
	pthread_mutex_lock(dinner->left_fork);
	print(dinner, "has taken a fork");
	pthread_mutex_lock(dinner->right_fork);
	print(dinner, "has taken a fork");
	print(dinner, "is eating");
	pthread_mutex_lock(&(dinner->data->meal_lock));
	dinner->last_meal = get_current_time();
	dinner->meals_eaten++;
	pthread_mutex_unlock(&(dinner->data->meal_lock));
	ft_ussleep(dinner->time_to_eat);
	pthread_mutex_unlock(dinner->right_fork);
	pthread_mutex_unlock(dinner->left_fork);
}

void	is_sleep(t_philo *dinner)
{
	print(dinner, "is sleeping");
	ft_ussleep(dinner->time_to_sleep);
}

void	is_think(t_philo *dinner)
{
	print(dinner, "is thinking");
}
