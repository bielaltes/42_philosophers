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

long long abs_time(t_game *game)
{
    struct timeval t;

    gettimeofday(&t, NULL);
    return ( 1000 * (game->start_time.tv_sec - t.tv_sec) + (game->start_time.tv_usec - t.tv_usec) / 1000);
}

void bsleep(int time)
{
	time += abs_time();
	while (abs_time() <= time)
		usleep(100);
}

void print_state(t_philo *philo, char *str)
{
	long long t;

	if ( abs_time() - philo->last >= philo->ttd)
	{
		philo->game->end = 1;
		write(1, ft_itoa(abs_time), ft_strlen(ft_itoa(abs_time)));
		write(1, " ", 1);
		write(1, ft_itoa(philo->n_philo), ft_strlen(ft_itoa(philo->n_philo)));
		write(1, " ", 1);
		write(1, D, ft_strlen(D));
	}
	else
	{
		write(1, ft_itoa(abs_time), ft_strlen(ft_itoa(abs_time)));
		write(1, " ", 1);
		write(1, ft_itoa(philo->n_philo), ft_strlen(ft_itoa(philo->n_philo)));
		write(1, " ", 1);
		write(1, str, ft_strlen(str));
	}
}

void eating(t_philo *philo)
{
	pthread_mutex_lock(philo->game->start);
	pthread_mutex_unlock(philo->game->start);
	if (!philo->game->ended)
	{
		pthread_mutex_lock(philo->lfork);
		print_state(philo,  F);
		pthread_mutex_lock(&philo->rfork);
		print_state(philo,  F);
		print_state(philo,  E);
		philo->last = abs_time;
		bsleep(philo->game->tte);
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(&philo->rfork);
		usleep(philo->game->tts);
		eating(philo);
	}
}

void anti_deadlock(t_philo *philo)
{
	pthread_mutex_lock(philo->game->start);
	pthread_mutex_unlock(philo->game->start);
	bsleep(100);
	eating(philo);
}