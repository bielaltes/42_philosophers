/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:40:43 by baltes-g          #+#    #+#             */
/*   Updated: 2023/04/06 11:49:36 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void error_exit(char *str, t_game *game)
{
	int	i;

	write(2, str, ft_strlen(str));
	pthread_mutex_destroy(&game->start);
	pthread_mutex_destroy(&game->print);
	i = 0;
	while (i < game->n_philo)
	{
		pthread_mutex_destroy(&game->philos[i].rfork);
		free(game->philos[i].str_num);
		++i;
	}
	free(game->philos);
	free(game->threads);
	exit(2);
}

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

int	intlen(int n)
{
	int	sum;

	sum = 0;
	if (n < 0)
		sum++;
	while (n != 0)
	{
		++sum;
		n /= 10;
	}
	return (sum);
}

int	absolut(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*especialet(void)
{
	char	*zero;

	zero = malloc(2);
	if (!zero)
		return (NULL);
	zero[0] = 48;
	zero[1] = '\0';
	return (zero);
}

char	*ft_itoa(int n)
{
	char	*new;
	int		i;
	int		len;

	len = intlen(n);
	i = 1;
	if (n == 0)
		return (especialet());
	new = malloc(sizeof(char) * (len +1));
	if (!new)
		return (NULL);
	if (n < 0)
	{
		*new = '-';
	}	
	while (n != 0)
	{
		new[len - i] = absolut(n % 10) + 48;
		n /= 10;
		++i;
	}
	new[len] = '\0';
	return (new);
}



