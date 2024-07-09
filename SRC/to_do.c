/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_do.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 06:56:51 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/09 09:24:38 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void    *examine(void *arg)
{
    t_philo *philo;
    int     i;
    double    thinkin_time;

    i = 0;
    philo = (t_philo *)arg;
    while(i < philo->cpu->nb_philo)
    {
        thinkin_time = philo->cpu->time_to_die + philo[i].last_eat;
        if (ft_get_time() >= thinkin_time)
        {
            pthread_mutex_lock(philo->cpu->print_lock);
            printf("dead\n");
            philo->cpu->dead = true;
            pthread_mutex_unlock(philo->cpu->print_lock);
            pthread_exit(NULL);
        }
        i++;
        if (i == philo->cpu->nb_philo)
            i = 0;
    }
    return (NULL);
}

void    ft_sleep(t_philo *philo)
{
    if (philo->eat_count == philo->cpu->must_eat_nb)
        return ;
    data_logger(philo, "is sleeping");
    ft_usleep(philo->cpu->time_to_sleep, philo);
}

void    ft_think(t_philo *philo)
{
    if (philo->eat_count == philo->cpu->must_eat_nb)
        return ;
    data_logger(philo, "is thinking");
    philo->thinking = true;
}

void    ft_eat(t_philo *philo)
{
    pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;

    philo->thinking = false;
    left_fork = &philo->cpu->forks[philo->id - 1];
    if (philo->id == philo->cpu->nb_philo)
        right_fork = &philo->cpu->forks[0];
    else
        right_fork = &philo->cpu->forks[philo->id];
    pthread_mutex_lock(left_fork);
    data_logger(philo, "has taken a fork");
    pthread_mutex_lock(right_fork);
    data_logger(philo, "has taken a fork");
    data_logger(philo, "is eating");
    ft_usleep(philo->cpu->time_to_eat, philo);
    philo->eat_count++;
    pthread_mutex_unlock(left_fork);
    pthread_mutex_unlock(right_fork);
}