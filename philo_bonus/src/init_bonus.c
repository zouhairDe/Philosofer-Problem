/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 01:38:15 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/23 02:10:03 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_logs(t_philo *philo, char *did)
{
	sem_wait(philo->data->write);
	if (!philo->data->over)
	{
		printf("%ld %d %s\n", get_time() - philo->data->start, philo->id, did);
		sem_post(philo->data->write);
	}
	sem_post(philo->data->write);
}

int	allocate_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->number);
	if (!data->philos)
		return (printf("Error:\nMalloc failed\n"));
	i = 0;
	while (i < data->number)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].data = data;
		data->philos[i].last_eat = get_time();
		i++;
	}
	return (0);
}

int	init(t_data *data, int ac, char **av)
{
	int	i;

	data->number = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = -1;
	if (data->number < 1 || data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1 || (ac == 6 && data->must_eat < -1))
		return (printf("Error:\nIncorrect arguments\n"));
	sem_unlink("lock");
	sem_unlink("read");
	sem_unlink("end");
	sem_unlink("forks");
	data->forks = sem_open("forks", O_CREAT, 0700, data->number);
	data->lock = sem_open("lock", O_CREAT, 0700, 1);
	data->read = sem_open("read", O_CREAT, 0700, 1);
	data->end = sem_open("end", O_CREAT, 0700, 1);
	if (allocate_philos(data))
		return (1);
	return (0);
}
