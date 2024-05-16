/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:26:48 by omghazi           #+#    #+#             */
/*   Updated: 2024/05/10 00:21:23 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write (1, &s[i], 1);
		i++;
	}
}

void	*check_death(void *p)
{
	t_philo	*philos;
	t_table	*table;
	size_t	time;

	philos = (t_philo *)p;
	table = philos->table;
	while (1)
	{
		time = get_current_time() - table->start_time;
		if (philos->eating_meals == philos->table->meals_nbr)
			break ;
		if (time - philos->last_meals > table->time_to_die)
		{
			sem_wait(philos->table->sem_console);
			(ft_putnbr(time), ft_putstr("\t"));
			(ft_putnbr(philos->id), ft_putstr("\t"));
			ft_putstr("died\n");
			sem_post(philos->table->sem_finished);
		}
		ft_ussleep(1);
	}
	sem_post(philos->table->sem_finished);
	return (NULL);
}

int	stop_process(t_philo **philo, t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philos_nbr)
		kill((*philo)[i].process_id, SIGTERM);
	return (EXIT_FAILURE);
}

void	*wait_death(void *p)
{
	t_philo		**philos;
	t_table		*table;

	philos = (t_philo **)p;
	table = philos[0]->table;
	sem_wait(table->sem_finished);
	ft_ussleep(500);
	stop_process(philos, table);
	return (NULL);
}
