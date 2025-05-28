/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:55:58 by lserghin          #+#    #+#             */
/*   Updated: 2025/05/26 22:42:30 by lserghin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

sem_t sem;
pthread_mutex_t mutex;


void *routine(void *data)
{
    // sem_wait(&sem);
    sleep(1);
    pthread_mutex_lock(&mutex);
    
    // printf("%d\n", *(int *)data);
    // pthread_mutex_lock(&mutex);
    printf("hello im tread number %d\n", *(int *)data);
    pthread_mutex_lock(&mutex);
    pthread_mutex_unlock(&mutex);
    *(int *)data += 1;
    // sem_post(&sem);
    // pthread_mutex_unlock(&mutex);
    return NULL;
}

int main()
{
    int i = 0;
    // sem_init(&sem, 0,1);
    pthread_mutex_init(&mutex, NULL);
    int *a = malloc(sizeof(int));
    *a = 0;
    pthread_t treads[10];
    while (i < 10)
    {
        pthread_create(&treads[i], NULL, routine, a);
        i++;
    }
    i = 0;
    while (i < 10)
    {
        pthread_join(treads[i], NULL);
        i++;
    }
}