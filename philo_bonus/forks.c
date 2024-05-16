/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:26:46 by omghazi           #+#    #+#             */
/*   Updated: 2024/05/01 19:22:15 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	take_a_fork(t_philo *philo)
{
	sem_wait(philo->table->sem_forks);
	print(philo, "has taken a fork");
	return (1);
}

void	unlock_forks(t_philo *philo)
{
	sem_post(philo->table->sem_forks);
	sem_post(philo->table->sem_forks);
	print(philo, "is sleeping");
	ft_ussleep(philo->table->time_to_sleep);
}
