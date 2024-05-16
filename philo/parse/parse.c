/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:52:22 by omghazi           #+#    #+#             */
/*   Updated: 2024/04/26 08:20:30 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool	is_valid(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!is_digit(av[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	case_check(long args, int i)
{
	if (args == LONG_MAX)
		return (0);
	if (i == 1)
	{
		if (!first_args(args))
			return (0);
	}
	else if (i > 1 && i < 5)
	{
		if (!middle_args(args))
			return (0);
	}
	else if (i == 5)
		if (!last_args(args))
			return (0);
	return (1);
}

int	parse_input(char **av, int ac)
{
	int		i;
	long	args;

	i = 0;
	while (++i < ac)
	{
		if (!is_valid(av[i]))
			return (0);
		args = ft_atoi(av[i]);
		if (!case_check(args, i))
			return (0);
	}
	return (1);
}
