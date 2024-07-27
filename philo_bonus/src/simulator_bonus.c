/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 02:01:20 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/27 02:03:14 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_childes(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	while (++i < data->number)
		waitpid(-1, &status, 0);
}

void	think_abit(t_philo *philo)
{
	sem_wait(philo->data->write);
	printf("%ld %d is thinking\n", ft_round(get_time())
		- philo->data->start, philo->id);
	usleep(100);
	sem_post(philo->data->write);
}

int	simulate(t_data *data)
{
	int	i;
	int	status;

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
				if (data->philos[i].id % 2 != 0)
					think_abit(&data->philos[i]);
				eat(&data->philos[i]);
				ft_sleep(&data->philos[i]);
			}
		}
	}
	wait_childes(data);
	return (0);
}

void	killall(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number)
		kill(data->philos[i].pid, SIGKILL);
}

void	*check_death(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (1)
	{
		sem_wait(ph->data->lock);
		if (ft_round(ph->last_eat) + ph->data->time_to_die
			< ft_round(get_time()) && !ph->eating)
		{
			sem_wait(ph->data->end);
			ph->data->over = true;
			ph->dead = true;
			sem_wait(ph->data->write);
			printf("%.0f %d died\n", get_time() - ph->data->start, ph->id);
			killall(ph->data);
			sem_post(ph->data->end);
			sem_post(ph->data->lock);
			return (NULL);
		}
		sem_post(ph->data->lock);
		usleep(100);
	}
}

