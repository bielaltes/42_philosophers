/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:38:08 by baltes-g          #+#    #+#             */
/*   Updated: 2023/03/29 19:24:42 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <unistd.h> 
# include <pthread.h>

# define F "has taken a fork"
# define E "is eating"
# define T "is thinking"
# define D "died"

typedef struct s_philo
{
	int num;
	pthread_mutex_t *lfork;
	pthread_mutex_t rfork;
	int last_eat;
	long long last;
	t_game *game;
}	t_philo;

typedef struct s_game
{
	int n_philo;
	int ttd;
	int tte;
	int tts;
	int n_eats;
	t_filo *philos;
	pthread_t *threads;
	pthread_mutex_t start;
}	s_game;

#endif