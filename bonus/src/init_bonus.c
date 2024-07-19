/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:48:16 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/19 13:50:53 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo_bonus.h"

int    init_sem(t_data *data)
{
    sem_unlink("forks");
    sem_unlink("read");
    sem_unlink("lock");
    sem_unlink("dead");
    data->forks = sem_open("forks", O_CREAT, 0644, data->number);
    data->read = sem_open("read", O_CREAT, 0644, 1);
    data->lock = sem_open("lock", O_CREAT, 0644, 1);
    data->dead = sem_open("dead", O_CREAT, 0644, 0);
    if (data->forks == SEM_FAILED || data->read == SEM_FAILED
        || data->lock == SEM_FAILED || data->dead == SEM_FAILED)
        return (printf("Error\nSemaphores failed\n"), 1);
    return (0);
}

int	Initializer(t_data *data)
{
	int	i;

	i = -1;
	data->philos = (t_philo *)malloc(data->number * sizeof(t_philo));
	if (!data->philos)
		return (free(data->forks), -1);
	while (++i < data->number)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].dead = false;
		data->philos[i].last_meal = get_time();
		data->philos[i].thinking = false;
		data->philos[i].meals = 0;
	}
	if (init_sem(data))
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
	if (data->meals == -2 || data->eating_time < 0
		|| data->number < 0 || data->time_to_die < 0
		|| data->sleeping_time < 0)
		return (printf("Error\nAn argument is not valid\n"));
	if (Initializer(data))
		return (printf("Error\nInitializer faild\n"));
	return (0);
}
