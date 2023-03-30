/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:14:09 by baltes-g          #+#    #+#             */
/*   Updated: 2023/03/29 19:24:36 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void error_exit(char *str)
{
	write(2, str, ft_strlen(str));
	exit(2);
}

int main(int argc, char **argv)
{
	t_game game;
	int		err;
	int n;
	if (pthread_mutex_init(&game.start, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
	//if (!parse(argc, argv))
		//error_exit("Error: invalid input\n");
	init(argc, argv, &game);
	pthread_mutex_lock(&game.start);
	while (n < game.n_philo)
	{
		if (n % 2 == 0)
			err = pthread_create(&game.threads[n], NULL, &eating, (void *)&game.philos[n]);
		else
			err = pthread_create(&game.threads[n], NULL, &anti_deadlock, (void *)&game.philos[n]);
		if (err != 0)
					printf("\ncan't create thread\n");
		++n;
		pthread_join(game.threads[n], NULL);
	}
	gettimeofday(&game.start_time, NULL);
	pthread_mutex_unlock(&game.start);
}