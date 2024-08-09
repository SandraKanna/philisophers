/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:41:12 by sandra            #+#    #+#             */
/*   Updated: 2024/08/06 15:51:01 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

//odd philos sleep (time_to_sleep /2)
// odd philos take right fork first
// even philosophers start eating
// even take the left fork first
//every philo should have their own flag for death and meals_ok
//an additional thread (watcher) should monitor from the main function
//mutex for forks (left and right) and for printing
//handle the case of only one philo because only one fork
//use a custom sleep/wait function for more precision
//additional protection: if philo is eating it cannot die

typedef struct s_philo
{
	int				id;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				dead;
	int				meals_count;
	int				is_eating;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
}			t_philo;


typedef struct s_data
{
	int				total_philos;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				total_meals;
	int				start_time;
	t_philo			*philos;
	pthread_mutex_t	print;
}					t_data;


t_data *init_data(void)
{
	
}

int	main(int ac, char **av)
{
	t_data	*data;

	
	data = init_data();
	
}
