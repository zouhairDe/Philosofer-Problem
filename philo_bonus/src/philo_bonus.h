/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 01:18:38 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/28 03:47:49 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <stdbool.h>

struct	s_data;

typedef struct s_philo
{
	int				id;
	int				meals;
	long			last_eat;
	bool			dead;
	bool			eating;
	pid_t			pid;
	pthread_t		thread;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				number;
	int				eating_time;
	int				sleeping_time;
	int				time_to_die;
	int				meals;
	long			start;
	bool			over;
	t_philo			*philos;
	sem_t			*forks;
	sem_t			*write;
	sem_t			*lock;
	sem_t			*end;
}					t_data;

int		init(t_data *data, int ac, char **av);
int		ft_atoi(char *str);
int		is_number(char *str);
int		simulate(t_data *data);
long	ft_round(double nb);
void	init_forks(t_data *data);
void	eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	print_logs(t_philo *philo, char *did);
double	get_time(void);
// void	*monitor(void *data);
#endif