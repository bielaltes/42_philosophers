/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:32 by baltes-g          #+#    #+#             */
/*   Updated: 2023/04/27 17:42:52 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <unistd.h> 
# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>

# define F "has taken a fork"
# define E "is eating"
# define S "is sleeping"
# define T "is thinking"
# define D "died"

typedef struct s_game	t_game;

typedef struct s_philo
{
	char			*str_num;
	int				num;
	int				len_num;
	int				eaten;
	int				last_eat;
	int				alive;
	long long		last;
	pthread_t		ctrl;
	t_game			*game;
}	t_philo;

typedef struct s_game
{
	int				end;
	int				n_philo;
	int				ttd;
	int				tte;
	int				tts;
	int				n_eats;
	int				*pids;
	t_philo			*philos;
	sem_t			*start;
	sem_t			*print;
	sem_t			*forks;
	struct timeval	start_time;
}	t_game;

void			error_exit(char *str, t_game *game);
void			kill_philos(t_game *game);
int				parse(int argc, char **argv);
int				init(int argc, char **argv, t_game *game);
long long		abs_time(t_game *game);
void			bsleep(int time, t_philo *philo);
void			print_state(t_philo *philo, char *str);
void			eating(t_philo *philo);
void			anti_deadlock(t_philo *philo);
int				ft_atoi(const char *str);
size_t			ft_strlen(const char *str);
char			*ft_itoa(int n);

#endif