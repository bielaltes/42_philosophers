/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:10:15 by baltes-g          #+#    #+#             */
/*   Updated: 2023/04/06 12:45:30 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	abs_time(t_game *game)
{
    struct timeval	t;

    gettimeofday(&t, NULL);
    return ( 1000 * (t.tv_sec - game->start_time.tv_sec) + (t.tv_usec - game->start_time.tv_usec ) / 1000);
}

void	bsleep(int time, t_philo *philo)
{
	long long	t;
	
	if (time == 0)
		return;
	time += abs_time(philo->game);
	while (abs_time(philo->game) < time && !philo->game->end)
	{
		t = abs_time(philo->game);
		if (t - philo->last >= philo->game->ttd)
			print_state(philo, D);
		usleep(100);
	}
}

void	print_state(t_philo *philo, char *str)
{
	long long	t;
	char		*str_time;

	t = abs_time(philo->game);
	str_time = ft_itoa(t);
	if (!str_time)
		error_exit("error: malloc", philo->game);
	pthread_mutex_lock(&philo->game->print);
	if ( t - philo->last < philo->game->ttd && philo->game->end == 0)
		printf("%s %s %s\n", str_time, philo->str_num, str);
	else
	{
		if (philo->game->end == 0)
			printf("%s %s %s\n", str_time, philo->str_num, D);
		philo->game->end = 1;
	}
	free(str_time);
	pthread_mutex_unlock(&philo->game->print);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->start);
	pthread_mutex_unlock(&philo->game->start);
	if (philo->game->n_eats != -1 && philo->eaten == philo->game->n_eats)
		return;
	if (philo->game->end == 0)
	{
		pthread_mutex_lock(philo->lfork);
		print_state(philo,  F);
		if (philo->game->n_philo == 1)
			 return bsleep(philo->game->ttd +1, philo);
		pthread_mutex_lock(&philo->rfork);
		print_state(philo,  F);
		print_state(philo,  E);
		philo->last = abs_time(philo->game);
		philo->eaten++;
		bsleep(philo->game->tte, philo);
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(&philo->rfork);
		bsleep(philo->game->tts, philo);
		eating(philo);
	}
	else
	{
		print_state(philo, D);
	}
}

void	anti_deadlock(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->start);
	pthread_mutex_unlock(&philo->game->start);
	bsleep(1, philo);
	eating(philo);	
}