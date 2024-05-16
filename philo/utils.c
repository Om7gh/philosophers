/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:29:34 by omghazi           #+#    #+#             */
/*   Updated: 2024/05/09 23:32:35 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	is_space(char *s, int *i, int *sign)
{
	while ((*(s + *i) <= 13 && *(s + *i) >= 9) || *(s + *i) == ' ')
		(*i)++;
	if (*(s + *i) == '-' || *(s + *i) == '+')
	{
		if (*(s + *i) == '-')
			*sign *= -1;
		(*i)++;
	}
}

long	ft_atoi(char *s)
{
	int	res;
	int	sign;
	int	i;
	int	tmp;

	res = 0;
	tmp = 0;
	sign = 1;
	i = 0;
	if (!s)
		return (-1);
	is_space(s, &i, &sign);
	while (*(s + i) >= '0' && *(s + i) <= '9')
	{
		res = res * 10 + *(s + i) - '0';
		if (tmp > res || sign == -1)
			return (LONG_MAX);
		tmp = res;
		i++;
	}
	return (res * sign);
}

int	ft_ussleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	mr_propre(t_prog *init)
{
	free(init->philos->thread_id);
	free(init);
	free(init->philos);
	free(init->forks);
}
