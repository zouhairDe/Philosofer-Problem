/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:54:05 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/14 00:29:38 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_logs(t_philo *philo, char *did)
{
	double	timestamp;
	int		meals;
	int		over;
	
	pthread_mutex_lock(&philo->data->lock);
	meals = philo->meals;
	over = philo->data->over;
	pthread_mutex_unlock(&philo->data->lock);
	if (philo->data->meals == meals || over == true)
		return ;
	pthread_mutex_lock(&philo->data->read);
	timestamp = get_time() - philo->data->start;
	printf("%.0f %d %s\n", timestamp, philo->id, did);
	pthread_mutex_unlock(&philo->data->read);
}

void	spend_time(int duration, t_philo *philo)
{
	double  go;

	go = get_time();
	while (get_time() - go < (double)duration)
	{
		usleep(100);
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->over == true)
		{
			pthread_mutex_unlock(&philo->data->lock);
			break;
		}
		pthread_mutex_unlock(&philo->data->lock);
	}
}

void	ft_sleep(t_philo *philo)
{
	if (philo->meals == philo->data->meals || philo->data->over == true)
		return ;
	print_logs(philo, "is sleeping");
	spend_time(philo->data->sleeping_time, philo);
}

void	think(t_philo *philo)
{
	if (philo->meals == philo->data->meals || philo->data->over == true)
		return ;
	print_logs(philo, "is thinking");
	philo->thinking = true;
}

void	eat(t_philo *philo)
{
	int	meals;
	int	over;

	pthread_mutex_lock(&philo->data->lock);
	meals = philo->data->meals;
	over = philo->data->over;
	pthread_mutex_unlock(&philo->data->lock);
	if (philo->meals == meals || over == true)
		pthread_exit(NULL);
	if (philo->id % 2 == 0)
		usleep(100);
	pthread_mutex_lock(philo->l_fork);
	print_logs(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	print_logs(philo, "has taken a fork");
	philo->thinking = false;
	print_logs(philo, "is eating");
	spend_time(philo->data->eating_time, philo);
	pthread_mutex_lock(&philo->data->lock);
	philo->last_meal = get_time();
	philo->meals += 1;
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
