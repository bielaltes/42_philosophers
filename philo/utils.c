/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:40:43 by baltes-g          #+#    #+#             */
/*   Updated: 2023/04/28 09:57:37 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	neg;
	int	sum;

	neg = 1;
	sum = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		++str;
	if (*str == '-')
		neg = -1;
	if (*str == '+' || *str == '-')
		++str;
	while (*str >= '0' && *str <= '9')
	{
		sum = sum * 10 + *str - 48;
		++str;
	}
	return (sum * neg);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str && *str != '\0')
	{
		++str;
		++len;
	}
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
	{
		return (0);
	}
	if (n == 1)
	{
		return ((unsigned char)*s1 - (unsigned char)*s2);
	}	
	else if (*s1 == '\0' && *s2 == '\0')
	{
		return (0);
	}
	else if (*s1 == *s2)
	{
		++s1;
		++s2;
		return (ft_strncmp(s1, s2, n - 1));
	}
	else
	{
		return ((unsigned char)*s1 - (unsigned char)*s2);
	}
}
