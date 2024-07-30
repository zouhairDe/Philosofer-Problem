/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 02:28:10 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/30 02:40:57 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void cleanup(t_data *data)
{
    int i;

    for (i = 0; i < data->number; i++)
    {
        kill(data->philos[i].pid, SIGKILL);
        waitpid(data->philos[i].pid, NULL, 0);
    }

    sem_close(data->forks);
    sem_close(data->write);
    sem_close(data->lock);
    sem_close(data->end);

    sem_unlink("forks");
    sem_unlink("write");
    sem_unlink("lock");
    sem_unlink("end");

    free(data->philos);
}

void	spend_time(int duration, t_philo *philo)
{
	double	go;

	go = get_time();
	while (get_time() - go < (double)duration)
	{
		usleep(100);
		sem_wait(philo->data->lock);
		if (philo->data->over == true)
		{
			sem_post(philo->data->lock);
			break ;
		}
		sem_post(philo->data->lock);
	}
}

void	ft_sleep(t_philo *philo)
{
	long	time;

	if (philo->data->over || philo->dead || philo->data->number == 1)
		exit(0);
	if (philo->meals == philo->data->meals)
		exit(0);
	print_logs(philo, "is sleeping");
	time = get_time();
	spend_time(philo->data->sleeping_time, philo);
	print_logs(philo, "is thinking");
}
void eat(t_philo *philo)
{
    sem_wait(philo->data->lock);
    if (philo->data->over || philo->dead || philo->meals == philo->data->meals)
    {
        sem_post(philo->data->lock);
        exit(0);
    }
    sem_post(philo->data->lock);

    sem_wait(philo->data->forks);
    print_logs(philo, "has taken a fork");
    sem_wait(philo->data->forks);
    print_logs(philo, "has taken a fork");
    print_logs(philo, "is eating");
    
    sem_wait(philo->data->lock);
    philo->eating = true;
    philo->last_eat = get_time();
    philo->meals++;
    sem_post(philo->data->lock);
    
    spend_time(philo->data->eating_time, philo);
    
    sem_wait(philo->data->lock);
    philo->eating = false;
    sem_post(philo->data->lock);
    
    sem_post(philo->data->forks);
    sem_post(philo->data->forks);
}