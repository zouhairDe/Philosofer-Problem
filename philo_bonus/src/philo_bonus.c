/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 01:23:19 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/29 02:58:50 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int main(int ac, char **av)
{
	t_data	data;

	if (ac > 6 || ac < 5)
		return (printf("Error:\nIncorrect arguments number\n"));
	if (init(&data, ac, av))
		return (1);
	if (simulate(&data))
		return (1);
	printf("FINISHEDDDDDD\n");
	sem_close(data.forks);
	sem_close(data.write);
	sem_close(data.lock);
	sem_close(data.end);
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("lock");
	sem_unlink("end");
	free(data.philos);
	return (0);
}
