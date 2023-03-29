/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:37:55 by baltes-g          #+#    #+#             */
/*   Updated: 2023/03/29 19:24:34 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_t tid[2];
int counter;


void* doSomeThing(void *vargp)
{
	pthread_mutex_t *lock = vargp;
    pthread_mutex_lock(lock);
	
    counter += 1;
    printf("\n Job %d started\n", counter);

    usleep(2000000);

    printf("\n Job %d finished\n", counter);

    pthread_mutex_unlock(lock);

    return NULL;
}

int main(void)
{
    int err;
	pthread_mutex_t lock;
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

    for (int i = 0; i < 2; ++i)
    {
        err = pthread_create(&(tid[i]), NULL, doSomeThing, (void *)&lock);
        if (err != 0)
            printf("\ncan't create thread\n");
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_mutex_destroy(&lock);

    return 0;
}