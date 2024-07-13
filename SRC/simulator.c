/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:25:40 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/10 21:26:39 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating_done(t_data *data)
{
	int	i;
	int	finishers;

	i = 0;
	finishers = 0;
	while (i < data->number)
	{
		pthread_mutex_lock(&data->lock);
		if (data->philos[i].meals == data->meals)
			finishers += 1;
		pthread_mutex_unlock(&data->lock);
		i++;
	}
	if (finishers == data->number)
		return (0);
	return (1);
}

void	*keep_track(void *d)
{
	t_data *data;
	int		i;

	data = (t_data *)d;
	i = 0;
	while (i < data->number)
	{
		if (!eating_done(data))
			ft_done(&data->philos[i], 0);
		pthread_mutex_lock(&data->lock);
		if (ft_round(data->philos[i].last_meal) + data->time_to_die < ft_round(get_time()))
		{
			data->over = true;
			data->philos[i].dead = true;
			pthread_mutex_unlock(&data->lock);
			ft_done(&data->philos[i], 1);
		}
		pthread_mutex_unlock(&data->lock);
		i++;
		if (i == data->number)
			i = 0;
	}
	return (NULL);
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 == 0 || philo->id == philo->data->number)
		usleep(100);
	while(philo->dead == false)
	{
		eat(philo);
		ft_sleep(philo);
		think(philo);
	}
	pthread_exit(NULL);
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
		if (pthread_create(&data->philos[i].t, NULL, &routine, &data->philos[i]))
			return (-1);
		i++;
	}
	if (pthread_create(&data->eye, NULL, &keep_track, data))
		return (-1);
	pthread_join(data->eye, NULL);
	i = 0;
	while (i < data->number)
	{
		if (pthread_join(data->philos[i].t, NULL))
			return (-1);
		i++;
	}
	return (0);
}
