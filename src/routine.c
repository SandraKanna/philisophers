/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:52:53 by sandra            #+#    #+#             */
/*   Updated: 2024/08/13 15:52:44 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think(t_philo *philo)
{
	print_status(philo, "is thinking");
	// usleep_ms(philo->time_to_eat / 2);
}

static int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken left fork");
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken right fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken right fork");
		if (philo->total_philos == 1)
		{
			usleep_ms(philo->time_to_die);
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_lock(philo->death_lock);
			*philo->should_stop = 1;
			pthread_mutex_unlock(philo->death_lock);
			return (1);
		}
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken left fork");
	}
	return (0);
}

static int	eat(t_philo *philo)
{
	if (take_forks(philo) != 0)
		return (1);
	philo->is_eating = 1;
	print_status(philo, "is eating");
	pthread_mutex_lock(philo->meals_lock);
	philo->last_meal = get_cur_time();
	philo->meals_count++;
	pthread_mutex_unlock(philo->meals_lock);
	usleep_ms(philo->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo->is_eating = 0;
	print_status(philo, "has put down the forks");
	return (0);
}

static void	zzzleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	usleep_ms(philo->time_to_sleep);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (should_stop(philo) == 0)
	{
		// print_status(philo, "is stoping");
		if (eat(philo) != 0)
			break ;
		think(philo);
		zzzleep(philo);
	}
	return (arg);
}
