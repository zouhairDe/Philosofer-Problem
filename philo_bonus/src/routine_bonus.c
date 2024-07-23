/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 02:28:10 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/23 02:42:50 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sleep(t_philo *philo)
{
	long	time;

	if (philo->data->over || philo->dead || philo->data->number == 1)
		return ;
	if (philo->data->meals == philo->data->meals)
		return ;
	print_logs(&data->philos[i], "is sleeping");
	time = get_time();
	while (get_time() - time < philo->data->sleeping_time)
		usleep(100);
	print_logs(&data->philos[i], "is thinking");
}

void	eat(t_philo *philo)
{
	if (philo->data->over || philo->dead || philo->data->number == 1)
		return ;
	if (philo->data->meals == philo->data->meals)
		return ;
	sem_wait(philo->data->lock);
	sem_wait(philo->data->forks);
	print_logs(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_logs(philo, "has taken a fork");
	print_logs(philo, "is eating");
	philo->last_eat = get_time();
	sem_post(philo->data->lock);
	while (get_time() - philo->last_eat < philo->data->eating_time)
		usleep(100);
	philo->meals++;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	ft_sleep(philo);
}
