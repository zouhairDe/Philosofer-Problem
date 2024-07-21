/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:43:57 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/21 01:19:43 by zouddach         ###   ########.fr       */
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

struct	s_data;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				meals;
	bool			dead;
	bool			eating;
	pthread_t		t;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_data	*data;
}	t_philo;

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
	pthread_t		eye;
	pthread_mutex_t	*forks;
	pthread_mutex_t	read;
	pthread_mutex_t	lock;
	pthread_mutex_t	end;
}	t_data;

int		init(t_data *data, int ac, char **av);
int		ft_atoi(char *str);
int		is_number(char *str);
int		simulator(t_data *data);
// int		ft_done(t_philo *philo, int code);
long	ft_round(double nb);
void	init_forks(t_data *data);
void	eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	think(t_philo *philo);
void	print_logs(t_philo *philo, char *did);
double	get_time(void);

#endif