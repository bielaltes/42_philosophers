/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:10:15 by baltes-g          #+#    #+#             */
/*   Updated: 2023/03/31 14:44:24 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long abs_time(t_game *game)
{
    struct timeval t;

    gettimeofday(&t, NULL);
    return ( 1000 * (t.tv_sec - game->start_time.tv_sec) + (t.tv_usec - game->start_time.tv_usec ) / 1000);
}

void bsleep(int time, t_game *game)
{
	time += abs_time(game);
	while (abs_time(game) < time)
	{
		usleep(100);
	}
}

void print_state(t_philo *philo, char *str)
{
	long long t;

	t = abs_time(philo->game);
	pthread_mutex_lock(&philo->game->print);
	if ( t - philo->last < philo->game->ttd)
	{
		write(1, ft_itoa(t), ft_strlen(ft_itoa(t)));
		write(1, " ", 1);
		write(1, ft_itoa(philo->num), ft_strlen(ft_itoa(philo->num)));
		write(1, " ", 1);
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
	}
	else
		philo->game->end = 1;
	pthread_mutex_unlock(&philo->game->print);
}

void *eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->start);
	pthread_mutex_unlock(&philo->game->start);
	if (philo->game->end == 0)
	{
		pthread_mutex_lock(philo->lfork);
		print_state(philo,  F);
		pthread_mutex_lock(&philo->rfork);
		print_state(philo,  F);
		print_state(philo,  E);
		philo->last = abs_time(philo->game);
		bsleep(philo->game->tte, philo->game);
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(&philo->rfork);
		bsleep(philo->game->tts, philo->game);
		eating(philo);
		return NULL;
	}
	else
	{
		print_state(philo, D);
		return NULL;
	}
}

void *anti_deadlock(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->start);
	pthread_mutex_unlock(&philo->game->start);
	bsleep(100, philo->game);
	eating(philo);
	return (NULL);	
}