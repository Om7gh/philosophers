/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:59:06 by omghazi           #+#    #+#             */
/*   Updated: 2024/05/10 00:21:57 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print(t_philo *philo, char *s)
{
	size_t	cur_time;

	cur_time = get_current_time() - philo->table->start_time;
	sem_wait(philo->table->sem_console);
	ft_putnbr(cur_time);
	ft_putstr("\t");
	ft_putnbr(philo->id);
	ft_putstr("\t");
	ft_putstr(s);
	ft_putstr("\n");
	sem_post(philo->table->sem_console);
}

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

static void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar((n % 10) + 48);
}
