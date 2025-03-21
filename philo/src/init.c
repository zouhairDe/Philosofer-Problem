/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:24:09 by zouddach          #+#    #+#             */
/*   Updated: 2024/08/01 08:27:00 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_death(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->end);
	data->over = true;
	philo->dead = true;
	printf("%.0f %d died\n", get_time() - data->start, philo->id);
	pthread_mutex_unlock(&data->end);
	pthread_mutex_unlock(&data->read);
	pthread_mutex_unlock(&data->lock);
	return ;
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number)
	{
		data->philos[i].l_fork = &data->forks[i];
		if (data->number - 1 == i)
			data->philos[i].r_fork = &data->forks[0];
		else
			data->philos[i].r_fork = &data->forks[i + 1];
		i++;
	}
}

int	allocate_memory(t_data *data)
{
	int	i;

	i = -1;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->number);
	if (!data->forks)
		return (-1);
	data->philos = (t_philo *)malloc(data->number * sizeof(t_philo));
	if (!data->philos)
		return (free(data->forks), -1);
	while (++i < data->number)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].dead = false;
		data->philos[i].eating = false;
		data->philos[i].last_meal = ft_round(get_time());
		data->philos[i].meals = 0;
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (free(data->forks), free(data->philos), -1);
	}
	if (pthread_mutex_init(&data->read, NULL) || pthread_mutex_init(&data->lock
			, NULL) || pthread_mutex_init(&data->end, NULL))
		return (-1);
	return (0);
}

int	init(t_data *data, int ac, char **av)
{
	int	i;

	i = 0;
	while (av[++i])
		if (is_number(av[i]))
			return (printf("Parsing error\n| %s |: Is not valid\n", av[i]));
	data->number = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->eating_time = ft_atoi(av[3]);
	data->sleeping_time = ft_atoi(av[4]);
	data->meals = -1;
	data->over = false;
	if (ac == 6)
		data->meals = ft_atoi(av[5]);
	if (data->meals == -2 || data->eating_time <= 0
		|| data->number <= 0 || data->time_to_die <= 0
		|| data->sleeping_time <= 0)
		return (printf("Error\nAn argument is not valid\n"));
	if (allocate_memory(data))
		return (printf("Error\nMemory Allocaion faild\n"));
	return (0);
}
