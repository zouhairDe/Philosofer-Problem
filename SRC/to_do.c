/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_do.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 06:56:51 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/09 07:24:41 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void    ft_eat(t_philo *philo)
{
    pthread_mutex_t *fork_left;
	pthread_mutex_t *fork_right;

    fork_left = &philo->cpu->forks[philo->id - 1];
    if (philo->id == philo->cpu->nb_philo)
        fork_right = &philo->cpu->forks[philo->id - 1];
    else
        fork_right = &philo->cpu->forks[philo->id + 1];
    pthread_mutex_lock(fork_left);
    data_logger(philo, "has taken a fork");
    pthread_mutex_lock(fork_right);    
    data_logger(philo, "has taken a fork");
    data_logger(philo, "is eating");
    philo->eat_count++;
    ft_usleep(philo->cpu->time_to_eat, philo);
    pthread_mutex_unlock(fork_left);
    pthread_mutex_unlock(fork_right);
}