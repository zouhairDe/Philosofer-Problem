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
	{
		pthread_mutex_lock(&data->end);
		data->over = true;
		pthread_mutex_unlock(&data->end);
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
			return (NULL);//maybe khasni data->over = true; hna
		pthread_mutex_lock(&data->lock);
		pthread_mutex_lock(&data->read);
		if (ft_round(data->philos[i].last_meal) + data->time_to_die
			< ft_round(get_time()) && data->philos[i].eating == false)
		{
			pthread_mutex_lock(&data->end);
			data->over = true;
			data->philos[i].dead = true;
			printf("%.0f %d died\n", get_time() - data->start, i + 1);
			pthread_mutex_unlock(&data->end);
			pthread_mutex_unlock(&data->read);
			pthread_mutex_unlock(&data->lock);
			break ;
		}
		pthread_mutex_unlock(&data->read);
		pthread_mutex_unlock(&data->lock);
		i++;
		if (i == data->number)
			i = 0;
	}
	return (NULL);//forbidden
}

void	*routine(void *p)
{
	t_philo	*philo;
	bool	dead;

	philo = (t_philo *)p;
	if (philo->id % 2 == 0 || (philo->id == philo->data->number
			&& philo->data->number % 2))
		usleep(500);
	dead = philo->data->over;
	while (dead == false)
	{
		if (philo->data->number > 1)
		{
			eat(philo);
			ft_sleep(philo);
		}
		pthread_mutex_lock(&philo->data->end);
		dead = philo->data->over;
		pthread_mutex_unlock(&philo->data->end);
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
