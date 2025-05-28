/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:55:37 by lserghin          #+#    #+#             */
/*   Updated: 2025/05/24 18:43:27 by lserghin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

void ft_child_routine(int id)
{
    sem_t *sem = sem_open("/sem", 0);
    sem_wait(sem);
    printf("im child N %d\n", id);
    sem_post(sem);
    sem_close(sem);
    exit(0);
    return ;
}

int main()
{
    sem_t *sem = sem_open("/sem", O_CREAT, 0644, 1);
    pid_t pid[3];

    printf("Parent (PID %d): Waiting for %d children to finish...\n", getpid(), 3);
    for(int i = 0; i < 3; i++)
    {
        *(pid + i) = fork();
        if (*(pid + i) == 0)
            ft_child_routine(i + 1);
    }
    for (int i = 0; i < 3; i++)
        wait(NULL);
    sem_close(sem);
    sem_unlink("/sem");
    return 0;
}


sem_t   sem;

void *ft_routine(void *arg)
{
    sem_wait(&sem);
    sleep(1);
    printf("hello im a thread\n");
    sem_post(&sem);
    return NULL;
}

int main()
{
    pthread_t pths[10];
    pthread_t *current_th;

    sem_init(&sem, 0, 1);
    current_th = pths;
    while (current_th < pths + 10)
    {
        if (pthread_create(current_th++, NULL, ft_routine, NULL))
            return 1;
    }
    current_th = pths;
    while (current_th < pths + 10)
    {
        if (pthread_join(*current_th++, NULL))
            return 1;
    }
    return 0;
}