/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:47:12 by omghazi           #+#    #+#             */
/*   Updated: 2024/05/19 18:31:50 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_init(t_philo *philo, t_table *table, int i)
{
	char	*philo_pos;
	char	*sem_name;

	philo->table = table;
	philo->id = i + 1;
	philo->last_meals = 0;
	philo->eating_meals = 0;
	philo_pos = ft_itoa(philo->id);
	sem_name = ft_strjoin("/sem_", philo_pos);
	sem_unlink(sem_name);
	philo->sem_philo = sem_open(sem_name, O_CREAT, 0644, 1);
	free(philo_pos);
	free(sem_name);
}

int	create_philos(t_philo **philo, t_table *table)
{
	int	i;

	i = -1;
	*philo = (t_philo *)malloc(sizeof(t_philo) * table->philos_nbr);
	if (!(*philo))
		return (printf("%serror with malloc%s\n", RED, NC), 0);
	while (++i < table->philos_nbr)
		philo_init(&(*philo)[i], table, i);
	return (1);
}

static int	init_semaphores(t_table *table)
{
	sem_unlink("/sem_forks");
	sem_unlink("/sem_console");
	sem_unlink("/sem_finished");
	table->sem_console = sem_open("/sem_console", O_CREAT, 0644, 1);
	if (table->sem_console == SEM_FAILED)
		return (printf("%serror with sem_open%s\n", RED, NC), 0);
	table->sem_forks = sem_open("/sem_forks", O_CREAT, 0644, table->philos_nbr);
	if (table->sem_forks == SEM_FAILED)
		return (printf("%serror with sem_open%s\n", RED, NC), 0);
	table->sem_finished = sem_open("/sem_finished", O_CREAT, 0644, 1);
	if (table->sem_finished == SEM_FAILED)
		return (printf("%serror with sem_open%s\n", RED, NC), 0);
	sem_unlink("/sem_forks");
	sem_unlink("/sem_console");
	sem_unlink("/sem_finished");
	sem_wait(table->sem_finished);
	return (1);
}

int	init_table(t_philo **philo, t_table *table, char **av)
{
	(void)philo;
	table->philos_nbr = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->meals_nbr = -1;
	if (ft_atoi(av[5]) || ft_atoi(av[5]) == 0)
		table->meals_nbr = ft_atoi(av[5]);
	if (!init_semaphores(table))
		return (0);
	return (1);
}
