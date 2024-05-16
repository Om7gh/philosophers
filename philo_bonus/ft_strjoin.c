/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 23:33:48 by omghazi           #+#    #+#             */
/*   Updated: 2024/04/30 23:33:52 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*arr;
	size_t	index;
	size_t	jndex;

	if (!s1 || !s2)
		return (NULL);
	arr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!arr)
		return (NULL);
	index = 0;
	jndex = 0;
	while (s1[index])
	{
		arr[index] = s1[index];
		index++;
	}
	while (s2[jndex])
	{
		arr[index + jndex] = s2[jndex];
		jndex++;
	}
	arr[index + jndex] = 0;
	return (arr);
}
