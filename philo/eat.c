/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:10:15 by baltes-g          #+#    #+#             */
/*   Updated: 2023/03/29 19:24:33 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time(long long last)
{
	timeval t;

	gettimeoftheday(&t, NULL);
	return (last - t.tv_sec * 1000 - t.tv_usec / 1000);
}

long long	time(long long last)
{
	timeval t;

	gettimeoftheday(&t, NULL);
	return (last - t.tv_sec * 1000 - t.tv_usec / 1000);
}

void print_state(t_philo *philo, char *str)
{
	long long t;

	t = time(philo->last)
	if ( t >= philo->ttd)
		philo->game->end = 1;
	else
	{
		write(1, ft_itoa())
	}
}

void eating(t_philo *philo)
{
	if (!philo->game->ended)
	{
		pthread_mutex_lock(philo->lfork);
		print_state(philo,  F);
		pthread_mutex_lock(&philo->rfork);
		print_state(philo,  F);
		print_state(philo,  E);
		usleep(philo->game->tte);
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(&philo->rfork);
		usleep(philo->game->tts);
		eating(philo);
	}
}