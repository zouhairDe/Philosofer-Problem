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

void	*keep_track(void *d)
{
	t_data *data;
	int		i;

	data = (t_data *)d;
	i = 0;
	while (1)
	{
		if ((double)(data->philos[i].last_meal + data->time_to_die) > get_time())
		{
			print_logs(&data->philos[i], "died");
			data->over = true;
			data->philos[i].dead = true;
		}
		i++;
		if (i == data->number)
			i = 0;
	}
}

int	alive(t_data *data)
{
	if (data->over == true)
		return (0);
	return (1);
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 == 0 || philo->id == philo->data->number)
		usleep(100);
	while(alive(philo->data))
	{
		eat(philo);
		ft_sleep(philo);
		think(philo);
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
		if (pthread_create(&data->philos[i].t, NULL, &routine, &data->philos[i]))
			return (-1);
		i++;
	}
	if (pthread_create(&data->eye, NULL, &keep_track, data))
		return (-1);
	i = 0;
	while (i < data->number)
	{
		if (pthread_join(data->philos[i].t, NULL))
			return (-1);
		i++;
	}
	return (0);
}
