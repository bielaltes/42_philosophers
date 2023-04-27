/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:38 by baltes-g          #+#    #+#             */
/*   Updated: 2023/04/27 17:44:36 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	error_exit(char *str, t_game *game)
{
	int	i;

	write(2, str, ft_strlen(str));
	sem_close(game->start);
	sem_close(game->print);
	sem_close(game->forks);
	i = 0;
	while (i < game->n_philo)
	{
		free(game->philos[i].str_num);
		++i;
	}
	free(game->philos);
	free(game->pids);
	exit(2);
}

void	create_philo(t_game *game, int n)
{
	game->pids[n] = fork();
	if (game->pids[n] == -1)
		error_exit("can't create thread\n", game);
	else if (game->pids[n] == 0)
	{
		if (n % 2 == 1)
			eating(&game->philos[n]);
		else
			anti_deadlock(&game->philos[n]);
	}
}

void	kill_philos(t_game *game)
{
	int	count;
	int	status;

	count = 0;
	while (game->pids[count])
		kill(game->pids[count++], SIGTERM);
	while (game->end < game->n_philo)
	{
		waitpid(-1, &status, WUNTRACED);
		if (WEXITSTATUS(status) == 1)
			break ;
		if (WEXITSTATUS(status) == 0)
			game->end++;
	}
	error_exit("", game);
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
	gettimeofday(&game.start_time, NULL);
	while (n < game.n_philo)
		create_philo(&game, n++);
	bsleep(2 * game.n_philo, &game.philos[0]);
	sem_post(game.start);
	n = 0;
	while (game.end < game.n_philo)
	{
		waitpid(-1, &n, WUNTRACED);
		if (WEXITSTATUS(n) == 1)
			break ;
		if (WEXITSTATUS(n) == 0)
			game.end++;
	}
	kill_philos(&game);
}
