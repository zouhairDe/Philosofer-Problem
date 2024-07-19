/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:08:40 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/19 14:33:20 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	log(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	log(philo, "has taken a fork");
}

void	routine(t_philo *philo)
{
	while (1)
	{
		if (philo->id % 2 == 0 || philo->data->number == philo->id)
			usleep(100);
        if (philo->meals == philo->data->meals)
            exit(0);
		if (philo->data->over || philo->dead)
			break ;
		take_forks(philo);
		eat(philo);
		ft_sleep(philo);
		think(philo);
	}
    kill_all(philo->data);
	exit(0);
}

int simulator(t_data *data)
{
    int i;
    int status;

    i = -1;
    data->start = get_time();
    while (++i < data->number)
    {
        data->philos[i].pid = fork();
        if (data->philos[i].pid == 0)
        {
            routine(&data->philos[i]);
            exit(0);
        }
        else
		{
			perror("Error\nFork failed\n");
			return (-1);
		}
    }
    i = -1;
    while (++i < data->number)
        waitpid(-1, &status, 0);
    return (0);
}