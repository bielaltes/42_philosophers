/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:38:08 by baltes-g          #+#    #+#             */
/*   Updated: 2023/03/31 14:43:43 by baltes-g         ###   ########.fr       */
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
# include <sys/time.h>
# include "../libft/libft.h"

# define F "has taken a fork"
# define E "is eating"
# define T "is thinking"
# define D "died"

typedef struct s_game t_game;

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
	int end;
	int n_philo;
	int ttd;
	int tte;
	int tts;
	int n_eats;
	t_philo *philos;
	pthread_t *threads;
	pthread_mutex_t start;
	pthread_mutex_t print;
	struct timeval	start_time;
}	t_game;

void			error_exit(char *str);
int				init(int argc, char **argv, t_game *game);
long long		abs_time(t_game *game);
void			bsleep(int time, t_game* game);
void			print_state(t_philo *philo, char *str);
void			*eating(t_philo *philo);
void			*anti_deadlock(t_philo *philo);

#endif