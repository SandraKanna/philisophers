/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:22:24 by skanna            #+#    #+#             */
/*   Updated: 2024/07/20 22:57:23 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	usleep_ms(int ms)
{
	usleep(ms * 1000);
}

int	run_philo(t_data *structure)
{
	int	i;

	i = 0;
	structure->start_time = current_timestamp();
	while (i < structure->num_philo)
	{
		if (pthread_create(&structure->philos[i].thread, NULL, routine, &structure->philos[i]) != 0)
		{
			while (i > 0)
				pthread_detach(structure->philos[--i].thread);
			return (1);
		}
		i++;
	}
	while (1)
	{
		if (structure->all_ate == structure->num_philo)
		{
			pthread_mutex_unlock(&structure->death_lock);
			pthread_mutex_unlock(&structure->meals_lock);
			ft_putstr_fd("All philosophers have eaten.\n", 1);
			break ;
		}
		if (structure->death)
		{
			pthread_mutex_unlock(&structure->death_lock);
			pthread_mutex_unlock(&structure->meals_lock);
			ft_putstr_fd("A philosopher has died.\n", 1);
			break ;
		}
		pthread_mutex_unlock(&structure->death_lock);
		pthread_mutex_unlock(&structure->meals_lock);
		usleep(1000);
	}
	i = 0;
	while (i < structure->num_philo)
	{
		if (pthread_join(structure->philos[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}




// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg); 