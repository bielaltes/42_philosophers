/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:26 by baltes-g          #+#    #+#             */
/*   Updated: 2023/04/27 17:45:29 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	print_state(t_philo *philo, char *str)
{
	long long	t;
	char		*str_time;

	t = abs_time(philo->game);
	str_time = ft_itoa(t);
	if (!str_time)
		error_exit("error: malloc", philo->game);
	sem_wait(philo->game->print);
	printf("%s %s %s\n", str_time, philo->str_num, str);
	if (str[0] == 'd')
		exit(1);
	free(str_time);
	sem_post(philo->game->print);
}
