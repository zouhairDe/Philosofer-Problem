/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:25:36 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/19 14:31:06 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	spend_time(long time)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}

void	think(t_philo *philo)
{
	sem_wait(philo->data->lock);
	if (philo->data->number == 1 || philo->data->over || philo->dead)
	{
		sem_post(philo->data->lock);
		return ;
	}
	if (philo->data->meals == philo->meals)
	{
		sem_post(philo->data->lock);
		exit(0);//maybe i should call a function to kill all pids
	}
	sem_post(philo->data->lock);
	log(philo, "is thinking");
	spend_time(philo->data->sleeping_time);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->data->lock);
	if (philo->data->number == 1 || philo->data->over || philo->dead)
	{
		sem_post(philo->data->lock);
		return ;
	}
	if (philo->data->meals == philo->meals)
	{
		sem_post(philo->data->lock);
		exit(0);
	}
	log(philo, "is eating");
	philo->meals++;
	sem_post(philo->data->lock);
	spend_time(philo->data->eating_time);
	sem_wait(philo->data->lock);
	philo->last_meal = get_time();
	sem_post(philo->data->lock);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}
