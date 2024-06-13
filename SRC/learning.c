/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   learning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:54:20 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/09 23:01:55 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_printer(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	pthread_mutex_lock(philo->cpu->print_lock);
	printf("Philo %d is printing...", philo->id);
    sleep(0);
	pthread_mutex_unlock(philo->cpu->print_lock);
	return ;
}

void	ft_simple_functions(t_cpu *cpu, t_philo *philo)
{
	int	i;

	i = 0;printf("Start: ==> %f\n", cpu->start);
	while (i < cpu->nb_philo)
	{
		pthread_create(&philo[i].thread, NULL, (void *)ft_printer, &philo[i]);
		i++;
	}
	i = 0;
    while (i < cpu->nb_philo)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
}
