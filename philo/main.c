/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:14:09 by baltes-g          #+#    #+#             */
/*   Updated: 2023/04/06 12:09:57 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_game game;
	int		err;
	int n =0;
	if (pthread_mutex_init(&game.start, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
	//if (!parse(argc, argv))
		//error_exit("Error: invalid input\n");
	init(argc, argv, &game);
	pthread_mutex_lock(&game.start);
	pthread_mutex_init(&game.print, NULL);
	//ft_printf("%d\n", game.n_philo);
	while (n < game.n_philo)
	{
		if (n % 2 == 0)
			err = pthread_create(&game.threads[n], NULL, (void *)&eating, &game.philos[n]);
		else
			err = pthread_create(&game.threads[n], NULL, (void *)&anti_deadlock, &game.philos[n]);
		if (err != 0)
					printf("can't create thread\n");
		++n;
		
	}
	bsleep(2 * game.n_philo, &game.philos[0]);
	gettimeofday(&game.start_time, NULL);
	pthread_mutex_unlock(&game.start);
		//ft_printf("%d\n", game.n_philo);
	n = 0;
	while (n < game.n_philo)
	{
		pthread_join(game.threads[n], NULL);
		++n;	
	}
}
