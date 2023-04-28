/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:14:09 by baltes-g          #+#    #+#             */
/*   Updated: 2023/04/28 09:17:50 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_exit(char *str, t_game *game)
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
	return (0);
}

int	create_philo(t_game *game, int n)
{
	int	err;

	if (n % 2 == 1)
	{
		err = pthread_create(&game->threads[n],
				NULL, (void *)&eating, &game->philos[n]);
	}
	else
	{
		err = pthread_create(&game->threads[n],
				NULL, (void *)&anti_deadlock, &game->philos[n]);
	}
	if (err != 0)
		return (error_exit("can't create thread\n", game));
	++n;
	return (1);
}

void	control(t_game *game)
{
	int			i;
	int			dead;
	long long	t;

	dead = 0;
	while (game->end == 0 && !dead)
	{
		i = 0;
		while (i < game->n_philo)
		{
			t = abs_time(game);
			if (game->philos[i].eaten == game->n_eats)
				dead = 1;
			if (!dead && t - game->philos[i].last >= game->ttd)
			{
				print_state(&game->philos[i], D);
				dead = 1;
			}
			++i;
		}
	}
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		n;

	n = 0;
	if (!parse(argc, argv))
		return (1);
	if (!init(argc, argv, &game))
		return (1);
	if (game.n_philo == 0)
		return (error_exit("", &game));
	while (n < game.n_philo)
	{
		create_philo(&game, n);
		++n;
	}
	bsleep(2 * game.n_philo, &game.philos[0]);
	gettimeofday(&game.start_time, NULL);
	pthread_mutex_unlock(&game.start);
	control(&game);
	n = 0;
	while (n < game.n_philo)
		pthread_join(game.threads[n++], NULL);
	error_exit("", &game);
}
