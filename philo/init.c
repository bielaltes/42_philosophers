/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:12:13 by baltes-g          #+#    #+#             */
/*   Updated: 2023/03/31 13:32:39 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*int parse(int argc, char **argv)
{

}*/

int init(int argc, char **argv, t_game *game)
{
	int	i;

	i = 0;	
	game->end = 0;
	game->n_philo = ft_atoi(argv[1]);
	game->ttd = ft_atoi(argv[2]);
	game->tte = ft_atoi(argv[3]);
	game->tts = ft_atoi(argv[4]);
	if (argc == 6)
		game->n_eats = ft_atoi(argv[5]);
	else
		game->n_eats = -1;
	game->philos = malloc(game->n_philo *sizeof(t_philo));
	game->threads = malloc(game->n_philo *sizeof(pthread_t));
	if (!game->philos)
		error_exit("Error: malloc\n");
	while (i < game->n_philo)
	{
		pthread_mutex_init(&game->philos[i].rfork, NULL);
		game->philos[i].num = i;
		game->philos[i].last = 0;
		if (i != 0)
			game->philos[i].lfork = &game->philos[i-1].rfork;
		game->philos[i].game = game;
		++i;
	}
	game->philos[0].lfork = &game->philos[game->n_philo -1].rfork;
	return (1);
}