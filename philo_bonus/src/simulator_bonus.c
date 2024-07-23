/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 02:01:20 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/23 03:03:12 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	simulate(t_data *data)
{
	int	i;

	i = -1;
	data->start = get_time();
	while (++i < data->number)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid < 0)
			break ;
		else
		{
			data->philos[i].last_eat = get_time();
			pthread_create(&data->philos[i].thread, NULL, &check_death, &data->philos[i]);
			while (1)
			{
				eat(&data->philos[i]);
				ft_sleep(&data->philos[i]);
			}
		}
	}
	if (i >= 0)
	{
		while (--i >= 0)
			kill(data->philos[i].pid, SIGKILL);
		return (0);
	}
}

void	*check_death(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (1)
	{
		sem_wait(ph->data->lock);
		if (ft_round(data->ph[i].last_meal) + data->time_to_die
			< ft_round(get_time()))
		{
			sem_wait(ph->data->end);
			data->over = true;
			data->philos[i].dead = true;
			sem_wait(ph->data->write);
			printf("%.0f %d died\n", get_time() - ph->data->start, i + 1);
			sem_post(ph->data->end);
			sem_post(ph->data->lock);
			return (NULL);
		}
		sem_post(ph->data->lock);
		usleep(1000);
	}
}

