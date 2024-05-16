/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:59:09 by omghazi           #+#    #+#             */
/*   Updated: 2024/05/16 00:13:16 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	process_begin(t_philo **philos, t_table *table)
{
	int	i;

	table->start_time = get_current_time();
	i = -1;
	while (++i < table->philos_nbr)
	{
		(*philos)[i].process_id = fork();
		if ((*philos)[i].process_id == -1)
			return (printf("error with fork\n"), 0);
		if ((*philos)[i].process_id == 0)
			return (start_simulation(&((*philos)[i])));
	}
	if (pthread_create(&(table->death_thread), NULL, &wait_death, philos) != 0)
		return (printf("error with pthread create\n"), 0);
	if (pthread_join(table->death_thread, NULL) != 0)
		return (printf("error with pthread join\n"), 0);
	return (1);
}

int	start_simulation(t_philo *philo)
{
	pthread_t	thr;

	if (pthread_create(&thr, NULL, check_death, philo) != 0)
		return (ft_putstr("error with pthread_create"), 0);
	while (1)
	{
		if (philo->eating_meals == philo->table->meals_nbr)
			break ;
		take_a_fork(philo);
		take_a_fork(philo);
		print(philo, "is eating");
		sem_wait(philo->sem_philo);
		philo->eating_meals++;
		philo->last_meals = get_current_time() - philo->table->start_time;
		sem_post(philo->sem_philo);
		ft_ussleep(philo->table->time_to_eat);
		unlock_forks(philo);
		print(philo, "is thinking");
	}
	return (1);
}

int	wait_process(t_philo **philo, t_table *table)
{
	int	i;
	int	exit_code;

	i = -1;
	exit_code = 1;
	while (++i < table->philos_nbr)
		if (waitpid((*philo)[i].process_id, NULL, 0) == -1)
			exit_code = 0;
	return (exit_code);
}
