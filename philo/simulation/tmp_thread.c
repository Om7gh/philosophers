/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_thread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 10:10:42 by omghazi           #+#    #+#             */
/*   Updated: 2024/04/22 11:38:40 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	death(t_prog *is_death)
{
	int	dead;

	pthread_mutex_lock(&(is_death->dead_lock));
	dead = is_death->dead;
	pthread_mutex_unlock(&(is_death->dead_lock));
	return (dead);
}
