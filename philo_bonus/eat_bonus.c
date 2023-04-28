/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:53 by baltes-g          #+#    #+#             */
/*   Updated: 2023/04/28 09:49:47 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	abs_time(t_game *game)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (1000 * (t.tv_sec - game->start_time.tv_sec)
		+ (t.tv_usec - game->start_time.tv_usec) / 1000);
}

void	bsleep(int time, t_philo *philo)
{
	long long	t;

	if (time == 0)
		time = 1;
	time += abs_time(philo->game);
	while (abs_time(philo->game) < time && !philo->game->end)
	{
		t = abs_time(philo->game);
		usleep(100);
	}
}

void	control(t_philo *philo)
{
	int			dead;
	long long	t;

	dead = 0;
	while (philo->game->end == 0 && !dead)
	{
		t = abs_time(philo->game);
		if (philo->eaten == philo->game->n_eats)
			dead = 1;
		if (!dead && t - philo->last >= philo->game->ttd)
		{
			print_state(philo, D);
			dead = 1;
		}
		bsleep(10, philo);
	}
	bsleep(1000, philo);
	exit(1);
}

void	eating(t_philo *philo)
{
	if (pthread_create(&philo->ctrl, NULL, (void *)&control, (void *)philo))
		error_exit("error: phtread", philo->game);
	while (philo->game->end == 0)
	{
		sem_wait(philo->game->forks);
		print_state(philo, F);
		if (philo->game->n_philo == 1)
			return (bsleep(philo->game->ttd +1, philo));
		sem_wait(philo->game->forks);
		print_state(philo, F);
		print_state(philo, E);
		philo->last = abs_time(philo->game);
		bsleep(philo->game->tte, philo);
		philo->eaten++;
		sem_post(philo->game->forks);
		sem_post(philo->game->forks);
		if (philo->game->n_eats != -1 && philo->eaten == philo->game->n_eats)
			exit(0);
		print_state(philo, S);
		bsleep(philo->game->tts, philo);
		print_state(philo, T);
	}
}

void	anti_deadlock(t_philo *philo)
{
	bsleep(1, philo);
	eating(philo);
}
