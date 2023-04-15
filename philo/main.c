/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:14:09 by baltes-g          #+#    #+#             */
/*   Updated: 2023/04/15 18:25:40 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(char *str, t_game *game)
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
	exit(2);
}

void	create_philo(t_game *game, int n)
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
		error_exit("can't create thread\n", game);
	++n;
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		n;

	n = 0;
	if (!parse(argc, argv))
		return (1);
	init(argc, argv, &game);
	if (game.n_philo == 0)
		error_exit("", &game);
	while (n < game.n_philo)
	{
		create_philo(&game, n);
		++n;
	}
	bsleep(2 * game.n_philo, &game.philos[0]);
	gettimeofday(&game.start_time, NULL);
	pthread_mutex_unlock(&game.start);
	n = 0;
	while (n < game.n_philo)
	{
		pthread_join(game.threads[n], NULL);
		++n;
	}
	error_exit("", &game);
}
