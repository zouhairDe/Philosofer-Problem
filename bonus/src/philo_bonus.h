/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:43:57 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/19 14:20:05 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <fcntl.h>
# include <semaphore.h>

struct	s_data;

typedef struct s_philo
{
	int				id;
	double			last_meal;
	int				meals;
	bool			dead;
	bool			thinking;
    pid_t           pid;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				number;
	int				eating_time;
	int				sleeping_time;
	int				time_to_die;
	int				meals;
	double			start;
	bool			over;
	t_philo			*philos;
	pthread_t		eye;
	sem_t       	forks;
	sem_t       	read;
	sem_t       	lock;
	sem_t       	dead;
}	t_data;

double	get_time();
long	ft_round(double nb);
int		init(t_data *data, int ac, char **av);
int		ft_atoi(char *str);
int		is_number(char *str);
int		simulator(t_data *data);
void	log(t_philo *philo, char *str);
void	eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	think(t_philo *philo);
void	spend_time(int time);
#endif