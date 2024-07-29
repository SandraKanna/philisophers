/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/07/29 18:36:24 by skanna           ###   ########.fr       */
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
	long long		last_meal_time;
	int				meals_count;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	// pthread_mutex_t	last_meal_time_lock;
	pthread_t		thread;
	struct s_data	*data;//pas besoin si jai un watcher
}	t_philo;

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	long long		start_time;
	int				all_ate;
	int				death;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meals_lock;
}	t_data;

void		clean_struct(t_data *structure);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
t_data		*init_struct(char **av);
void		*ft_memset(void *arg, int c, size_t n);
long long	ft_atoll(const char *str, int *err);
int			run_philo(t_data *structure);
int			is_dead(t_philo *philo);
int			meals_completed(t_data *data, t_philo *philo);
void		*routine(void *arg);
long long	current_timestamp(void);
void		usleep_ms(int ms);
void		print_status(t_philo *philo, char *status);

#endif