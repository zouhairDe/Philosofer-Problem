/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:37:20 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/09 09:25:24 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_cpu
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_nb;
	bool			dead;
	double			start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_lock;
}		t_cpu;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			last_eat;
	bool			thinking;
	pthread_t		thread;
	t_cpu			*cpu;
}		t_philo;

int		ft_is_all_ints(int ac, char **av);
double	ft_get_time(void);
int		ft_atoi(char *str);
int		ft_copy_data(int ac, char **av, t_cpu *cpu);
int		ft_check_null(t_cpu *cpu);
void	data_logger(t_philo *philo, char *state);
void    simulator(t_cpu *cpu, t_philo *philo);
void    ft_eat(t_philo *philo);
void	ft_usleep(int time, t_philo *philo);
void    ft_think(t_philo *philo);
void    ft_sleep(t_philo *philo);
void    *examine(void *arg);
#endif