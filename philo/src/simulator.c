/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:25:40 by zouddach          #+#    #+#             */
/*   Updated: 2024/08/01 08:01:27 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating_done(t_data *data)
{
	int	i;
	int	finishers;
	int	meals;

	i = 0;
	finishers = 0;
	while (i < data->number)
	{
		pthread_mutex_lock(&data->lock);
		meals = data->philos[i].meals;
		pthread_mutex_unlock(&data->lock);
		if (meals == data->meals)
			finishers += 1;
		i++;
	}
	if (finishers == data->number)
	{
		pthread_mutex_lock(&data->lock);
		data->over = true;
		pthread_mutex_unlock(&data->lock);
		return (0);
	}
	return (1);
}

void	*keep_track(void *d)
{
	t_data	*data;
	int		i;

	data = (t_data *)d;
	i = 0;
	while (1)
	{
		if (!eating_done(data))
			return (NULL);
		pthread_mutex_lock(&data->lock);
		pthread_mutex_lock(&data->read);
		if (ft_round(data->philos[i].last_meal) + data->time_to_die
			<= ft_round(get_time()) && data->philos[i].eating == false)
		{
			set_death(data, &data->philos[i]);
			return (NULL);
		}
		pthread_mutex_unlock(&data->read);
		pthread_mutex_unlock(&data->lock);
		i++;
		if (i == data->number)
			i = 0;
	}
	return (NULL);
}

void	think_abit(t_philo *philo)
{
	print_logs(philo, "is thinking");
	usleep(200);
}

void	*routine(void *p)
{
	t_philo	*philo;
	bool	dead;

	philo = (t_philo *)p;
	if (philo->id % 2 == 0 || ((philo->id == philo->data->number
			&& philo->data->number % 2) && philo->data->number != 1))
		think_abit(philo);
	dead = philo->data->over;
	while (dead == false)
	{
		eat(philo);
		ft_sleep(philo);
		pthread_mutex_lock(&philo->data->lock);
		dead = philo->data->over;
		pthread_mutex_unlock(&philo->data->lock);
	}
	return (NULL);
}

int	simulator(t_data *data)
{
	int	i;

	i = 0;
	init_forks(data);
	data->start = get_time();
	while (i < data->number)
	{
		if (pthread_create(&data->philos[i].t, NULL,
				&routine, &data->philos[i]))
			return (-1);
		i++;
	}
	if (pthread_create(&data->eye, NULL, &keep_track, data))
		return (-1);
	pthread_join(data->eye, NULL);
	i = 0;
	while (i < data->number)
	{
		if (pthread_detach(data->philos[i].t))
			return (-1);
		i++;
	}
	return (0);
}
