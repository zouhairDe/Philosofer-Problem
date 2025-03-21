/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:54:05 by zouddach          #+#    #+#             */
/*   Updated: 2024/08/01 08:13:19 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_logs(t_philo *philo, char *did)
{
	double	timestamp;
	bool	over;
	int		meals;
	int		philo_meals;

	pthread_mutex_lock(&philo->data->lock);
	over = philo->data->over;
	meals = philo->data->meals;
	philo_meals = philo->meals;
	pthread_mutex_unlock(&philo->data->lock);
	if (over == true || meals == philo_meals)
		return ;
	pthread_mutex_lock(&philo->data->read);
	timestamp = get_time() - philo->data->start;
	printf("%.0f %d %s\n", timestamp, philo->id, did);
	pthread_mutex_unlock(&philo->data->read);
}

void	spend_time(int duration, t_philo *philo)
{
	double	go;

	go = get_time();
	while (get_time() - go < (double)duration)
	{
		usleep(100);
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->over)
		{
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->lock);
	}
}

void	ft_sleep(t_philo *philo)
{
	int		meals;
	int		over;

	pthread_mutex_lock(&philo->data->lock);
	meals = philo->data->meals;
	over = philo->data->over;
	pthread_mutex_unlock(&philo->data->lock);
	if (philo->meals == meals || over == true)
		return ;
	if (philo->data->number == 1)
		return ;
	pthread_mutex_lock(&philo->data->lock);
	philo->eating = false;
	pthread_mutex_unlock(&philo->data->lock);
	print_logs(philo, "is sleeping");
	spend_time(philo->data->sleeping_time, philo);
	print_logs(philo, "is thinking");
}

void	eat(t_philo *philo)
{
	int	meals;
	int	over;

	pthread_mutex_lock(&philo->data->lock);
	meals = philo->data->meals;
	over = philo->data->over;
	pthread_mutex_unlock(&philo->data->lock);
	if (philo->meals == meals || over)
		return ;
	pthread_mutex_lock(philo->l_fork);
	print_logs(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	print_logs(philo, "has taken a fork");
	print_logs(philo, "is eating");
	pthread_mutex_lock(&philo->data->lock);
	philo->eating = true;
	philo->last_meal = ft_round(get_time());
	philo->meals++;
	pthread_mutex_unlock(&philo->data->lock);
	spend_time(philo->data->eating_time, philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
