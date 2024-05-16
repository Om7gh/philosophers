/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:54:41 by omghazi           #+#    #+#             */
/*   Updated: 2024/04/30 21:17:53 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	first_args(int av)
{
	if (av <= 0 || av > 200)
		return (0);
	return (1);
}

int	middle_args(int av)
{
	if (av < 60 || av <= 0)
		return (0);
	return (1);
}

int	last_args(int av)
{
	if (av < 0)
		return (0);
	return (1);
}
