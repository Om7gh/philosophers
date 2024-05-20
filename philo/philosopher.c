/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:50:15 by omghazi           #+#    #+#             */
/*   Updated: 2024/05/19 18:19:11 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	mr_clean_pro_max(t_prog *init, int *i)
{
	if (init)
	{
		pthread_mutex_destroy(&(init->dead_lock));
		pthread_mutex_destroy(&(init->write_lock));
		pthread_mutex_destroy(&(init->meal_lock));
		pthread_mutex_destroy(&init->forks[*i]);
	}
}

int	main(int ac, char **av)
{
	t_philo	*philos;
	t_prog	*init;
	int		i;

	if (ac < 5 || ac > 6)
		return (printf("%sinvalid argument%s\n", RED, NC), 1);
	if (!parse_input(av, ac))
		return (printf("%sinput parse error%s\n", RED, NC), 1);
	philos = philos_data_init(av);
	if (!philos)
		return (EXIT_FAILURE);
	init = life_cycle_init(philos);
	if (!init)
		return (free(philos->thread_id), free(philos), philos = NULL, \
				EXIT_FAILURE);
	if (!start_routine(init))
		return (free(init->forks), free(init), free(philos->thread_id), \
			free(philos), EXIT_FAILURE);
	i = -1;
	while (++i < philos->num_of_philos)
		mr_clean_pro_max(init, &i);
	mr_propre(init);
	return (EXIT_SUCCESS);
}
