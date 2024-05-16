/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:30:45 by omghazi           #+#    #+#             */
/*   Updated: 2024/05/16 00:17:29 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	mr_propre(t_philo *philos, t_table *table, int exit_code)
{
	free(philos);
	sem_close(table->sem_forks);
	sem_close(table->sem_console);
	sem_close(table->sem_finished);
	return (exit_code);
}

int	main(int ac, char **av)
{
	t_philo	*philos;
	t_table	table;
	int		exit_code;

	exit_code = EXIT_SUCCESS;
	if (ac < 5 || ac > 6)
		return (printf("%sInvalid argument%s\n", RED, NC), EXIT_FAILURE);
	if (!parse_input(av, ac))
		return (printf("%sInvalid input%s\n", RED, NC), EXIT_FAILURE);
	if (!init_table(&philos, &table, av))
		return (EXIT_FAILURE);
	if (table.meals_nbr == 0)
		return (EXIT_SUCCESS);
	if (!create_philos(&philos, &table))
		return (EXIT_FAILURE);
	if (!process_begin(&philos, &table))
		exit_code = stop_process(&philos, &table);
	if (!wait_process(&philos, &table))
		return (mr_propre(philos, &table, EXIT_FAILURE));
	return (mr_propre(philos, &table, exit_code));
}
