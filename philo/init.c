/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:12:13 by baltes-g          #+#    #+#             */
/*   Updated: 2023/04/15 18:26:45 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_aux(int argc, char **argv)
{
	int	i;

	while (argc != 1)
	{
		i = 0;
		if (ft_strlen(argv[argc -1]) == 0)
		{
			printf("error: invalid input\n");
			return (0);
		}
		while (argv[argc -1][i] != '\0')
		{
			if (!(argv[argc -1][i] >= '0' && argv[argc -1][i] <= '9') ||
				ft_strlen(argv[argc -1]) > 9)
			{
				printf("error: invalid input\n");
				return (0);
			}
			++i;
		}
		--argc;
	}
	return (1);
}

int	parse(int argc, char **argv)
{
	if (!(argc == 6 || argc == 5))
	{
		printf("error: invalid input\n");
		return (0);
	}
	return (parse_aux(argc, argv));
}

void	create_philos(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->n_philo)
	{
		if (pthread_mutex_init(&game->philos[i].rfork, NULL) != 0)
			error_exit("error: mutex\n", game);
		game->philos[i].num = i;
		game->philos[i].last = 0;
		game->philos[i].alive = 1;
		game->philos[i].eaten = 0;
		game->philos[i].str_num = ft_itoa(i);
		if (!game->philos[i].str_num)
			error_exit("error: malloc\n", game);
		game->philos[i].len_num = ft_strlen(game->philos[i].str_num);
		if (i != 0)
			game->philos[i].lfork = &game->philos[i -1].rfork;
		game->philos[i].game = game;
		++i;
	}
}

int	init(int argc, char **argv, t_game *game)
{
	game->end = 0;
	game->n_philo = ft_atoi(argv[1]);
	game->ttd = ft_atoi(argv[2]);
	game->tte = ft_atoi(argv[3]);
	game->tts = ft_atoi(argv[4]);
	if (argc == 6)
		game->n_eats = ft_atoi(argv[5]);
	else
		game->n_eats = -1;
	game->philos = malloc(game->n_philo * sizeof(t_philo));
	game->threads = malloc(game->n_philo * sizeof(pthread_t));
	if (!game->philos || !game->threads)
		error_exit("Error: malloc\n", game);
	if (pthread_mutex_init(&game->start, NULL) != 0
		|| pthread_mutex_init(&game->print, NULL) != 0)
		error_exit("error: mutex\n", game);
	pthread_mutex_lock(&game->start);
	create_philos(game);
	game->philos[0].lfork = &game->philos[game->n_philo -1].rfork;
	return (1);
}
