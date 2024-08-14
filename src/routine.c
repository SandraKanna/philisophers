/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:52:53 by sandra            #+#    #+#             */
/*   Updated: 2024/08/14 16:23:57 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void	think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

static int	take_forks(t_philo *philo)
{
	if (philo->total_philos == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken the only fork");
		usleep_ms(philo->time_to_die);
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
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
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken left fork");
	}
	return (0);
}

static int	eat(t_philo *philo)
{
	if (take_forks(philo) != 0)
		return (1);
	pthread_mutex_lock(&philo->data->meals_lock);
	philo->is_eating = 1;
	philo->last_meal = get_cur_time();
	philo->meals_count++;
	pthread_mutex_unlock(&philo->data->meals_lock);
	print_status(philo, "is eating");
	usleep_ms(philo->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	print_status(philo, "has put down the forks");
	pthread_mutex_lock(&philo->data->meals_lock);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->data->meals_lock);
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
	if (philo->id % 2 == 0)
		usleep_ms(1);
	// while (should_stop(philo) == 0)
	while (1)
	{
		if (should_stop(philo))
			break ;
		if (eat(philo) != 0)
			break ;
		if (should_stop(philo))
			break ;
		think(philo);
		if (should_stop(philo))
			break ;
		zzzleep(philo);
		if (should_stop(philo))
			break ;
	}
	return (NULL);
}
