/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/08/13 11:38:36 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> //delete after debugs
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	int				total_philos;	
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				start_time;
	int				last_meal;
	int				is_eating;
	int				meals_count;
	int				*stop;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*death_lock;
	pthread_mutex_t	*meals_lock;
	pthread_mutex_t	*print_lock;
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

void		clean_struct(t_data *structure, int size);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
t_data		*init_struct(char **av);
void		*ft_memset(void *arg, int c, size_t n);
long long	ft_atoll(const char *str, int *err);
int			run_philo(t_data *structure, int size);
int			is_dead(t_philo *philo);
int			meals_completed(t_data *data, t_philo *philo);
void		*routine(void *arg);
long long	get_cur_time(void);
void		usleep_ms(int ms);
void		print_status(t_philo *philo, char *status);
int			ft_atoi(const char *str);


#endif