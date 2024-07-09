/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:37:20 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/09 09:23:00 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool    alive(t_philo *philo)
{
    pthread_mutex_lock(philo->cpu->print_lock);
    if (philo->dead == true)
    {
        pthread_exit(NULL);
        return (false);
    }
    pthread_mutex_unlock(philo->cpu->print_lock);
    if (philo->eat_count != philo->cpu->must_eat_nb && philo->cpu->must_eat_nb != -1)
        return (false);
    return (true);
}

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    // pthread_mutex_lock(philo->cpu->print_lock);
    if (philo->id % 2 == 0 || philo->id == philo->cpu->nb_philo)
        ft_usleep(1, philo);
    while(alive(philo))
    {
        ft_eat(philo);
        philo->last_eat = ft_get_time();
        ft_sleep(philo);
        ft_think(philo);
    }
    exit(1);
    return (NULL);
}

void    simulator(t_cpu *cpu, t_philo *philo)
{
    int         i;
    pthread_t   examiner;

    i = 0;
    cpu->start = ft_get_time();
    while (i < cpu->nb_philo)
    {
        if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
        {
            printf("Error: pthread_create\n");
            exit(1);
        }
        i++;
    }
    if (pthread_create(&examiner, NULL, &examine, philo) != 0)
    {
        printf("Error: pthread_create\n");
        exit(1);
    }
    i = 0;
    while (i < cpu->nb_philo)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
}