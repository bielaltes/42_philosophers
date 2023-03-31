# include "philo.h"

#include "philo.h"
t_game game;

void error_exit(char *str)
{
	write(2, str, ft_strlen(str));
	exit(2);
}

int main(int argc, char **argv)
{
	
	//int		err;
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
	ft_printf("%d\n", game.n_philo);
	gettimeofday(&game.start_time, NULL);
	while (n < game.n_philo)
	{
		/*if (n % 2 == 0)
			err = pthread_create(&game.threads[n], NULL, (void *)&eating, (void *)&game.philos[n]);
		else
			err = pthread_create(&game.threads[n], NULL, (void *)&anti_deadlock, (void *)&game.philos[n]);
		if (err != 0)
					printf("can't create thread\n");*/
		write(1, ft_itoa(abs_time(&game)), ft_strlen(ft_itoa(abs_time(&game))));
		write(1, "\n", 1);
		bsleep(200, &game);
		++n;

	}
	bsleep(2 * game.n_philo, &game);
	gettimeofday(&game.start_time, NULL);
	pthread_mutex_unlock(&game.start);
		ft_printf("%d\n", game.n_philo);
	//while (1) 
		//write(1, "h", 1);
}