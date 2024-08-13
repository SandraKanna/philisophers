/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:00:33 by derjavec          #+#    #+#             */
/*   Updated: 2024/08/08 13:18:54 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philosopher
{
	long long				t_last_meal;
	struct s_rules			*rules;
	pthread_t				thread_id;
	int						id;
	int						x_ate;
	int						left_fork_id;
	int						right_fork_id;
}						t_philosopher;

typedef struct s_rules
{
	pthread_mutex_t		meal_check;
	pthread_mutex_t		ate_check;
	pthread_mutex_t		dead_check;
	pthread_mutex_t		*forks;
	pthread_mutex_t		writing;
	long long			first_timestamp;
	t_philosopher		*phi;
	int					philo_quantity;
	int					philo_ate_all;
	int					time_until_death;
	int					time_to_eat;
	int					time_to_sleep;
	int					full_philo_quantity;
	int					dead;
}	t_rules;
long long	timestamp(void);
size_t		ft_strlen( const char *c);
void		ft_error(char *msg, t_rules *rules);
void		wait(long long time, t_rules *rules);
void		init(t_rules *rules, int *data);
void		philo_threads(t_rules *rules);
void		check_if_philo_died(t_rules *rules);
void		*philosopher_rutine(void *void_phi);
void		print_action(t_rules *rules, int id, char *str);
void		clean_threads(t_rules *rules, t_philosopher *phi);
int			ft_atoi(const char *str, t_rules *rules);
#endif