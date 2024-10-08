/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/08/15 15:32:30 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	int				total_philos;	
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat;
	long long		start_time;
	long long		last_meal;
	int				is_eating;
	int				meals_count;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				stop;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	meals_lock;
	pthread_mutex_t	print_lock;
}					t_data;

//main functions
t_data		*initialize(char **av);
int			manage_philos(t_data *structure, int size);
void		*philo_lives(void *arg);
int			should_stop(t_philo *philo);
void		monitor_end(t_data *data, int size);
void		kill_zombies(t_data *data, int size);
void		destroy_mutex(t_data *structure, int size);

//auxiliar functions
long long	get_cur_time(void);
void		usleep_ms(long long sleep);
void		print_status(t_philo *philo, char *status);
void		free_data(t_data *structure);
void		err_msg(char *msg);
size_t		ft_strlen(const char *str);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_atoi(const char *str);

#endif