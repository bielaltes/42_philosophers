/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:48 by baltes-g          #+#    #+#             */
/*   Updated: 2023/04/28 09:59:07 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
				ft_strlen(argv[argc -1]) > 9 ||
					(ft_strlen(argv[argc -1]) == 10 &&
					ft_strncmp(argv[argc -1], "2147483647", 10) > 0))
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
		game->philos[i].num = i;
		game->philos[i].last = 0;
		game->philos[i].alive = 1;
		game->philos[i].eaten = 0;
		game->philos[i].str_num = ft_itoa(i + 1);
		if (!game->philos[i].str_num)
			error_exit("error: malloc\n", game);
		game->philos[i].len_num = ft_strlen(game->philos[i].str_num);
		game->philos[i].game = game;
		++i;
	}
}

void	init_sems(t_game *game)
{
	sem_unlink("sem_forks");
	sem_unlink("sem_start");
	sem_unlink("sem_print");
	game->forks = sem_open("sem_forks", O_CREAT | O_EXCL, 0644, game->n_philo);
	game->start = sem_open("sem_start", O_CREAT | O_EXCL, 0644, 1);
	game->print = sem_open("sem_print", O_CREAT | O_EXCL, 0644, 1);
	if (game->forks == SEM_FAILED
		|| game->start == SEM_FAILED
		|| game->print == SEM_FAILED)
		error_exit("error: sem\n", game);
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
	game->pids = malloc(game->n_philo * sizeof(int));
	if (!game->philos)
		error_exit("Error: malloc\n", game);
	init_sems(game);
	sem_wait(game->start);
	create_philos(game);
	return (1);
}
