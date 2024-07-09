/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:37:20 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/09 07:19:06 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool    alive(t_philo *philo)
{
    if (philo->dead == true)
        pthread_exit(NULL);
    if (philo->eat_count != philo->cpu->must_eat_nb && philo->cpu->must_eat_nb != -1)
        return (false);
    return (true);
}

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    // pthread_mutex_lock(philo->cpu->print_lock);
    philo->last_eat = ft_get_time();
    while(alive(philo))
    {
        ft_eat(philo);
        // ft_sleep(philo);
        // ft_think(philo);
    }
    return (NULL);
}

void    simulator(t_cpu *cpu, t_philo *philo)
{
    int i;

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
    i = 0;
    while (i < cpu->nb_philo)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
}