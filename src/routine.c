/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:52:53 by sandra            #+#    #+#             */
/*   Updated: 2024/07/29 18:36:31 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	think(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	print_status(philo, "is thinking");
	usleep_ms(philo->data->time_to_eat / 2);
	return (0);
}

static int	take_forks(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(philo->left_fork) != 0)
		{
			ft_putstr_fd("Error: mutex lock failed for left fork\n", 2);
			return (1);
		}
		print_status(philo, "has taken left fork");
		if (pthread_mutex_lock(philo->right_fork) != 0)
		{
			pthread_mutex_unlock(philo->left_fork);
			ft_putstr_fd("Error: mutex lock failed for right fork\n", 2);
			return (1);
		}
		print_status(philo, "has taken right fork");
	}
	else
	{
		if (pthread_mutex_lock(philo->right_fork) != 0)
		{
			ft_putstr_fd("Error: mutex lock failed for right fork\n", 2);
			return (1);
		}
		print_status(philo, "has taken right fork");
		if (pthread_mutex_lock(philo->left_fork) != 0)
		{
			pthread_mutex_unlock(philo->right_fork);
			ft_putstr_fd("Error: mutex lock failed for left fork\n", 2);
			return (1);
		}
		print_status(philo, "has taken left fork");
	}
	return (0);
}

static int	eat(t_philo *philo)
{
	if (take_forks(philo) != 0)
		return (1);
	print_status(philo, "is eating");
	philo->last_meal_time = current_timestamp();
	usleep_ms(philo->data->time_to_eat);
	//update meal for this philo after sleep
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	print_status(philo, "has put down the forks");
	return (0);
}

static int	sleep_philo(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	print_status(philo, "is sleeping");
	usleep_ms(philo->data->time_to_sleep);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		if (think(philo) != 0)
			break ;
		if (eat(philo) != 0)
			break ;
		if (sleep_philo(philo) != 0)
			break ;
		if (meals_completed(data, philo) != 0)
			break ;
		pthread_mutex_lock(&data->death_lock);
		if (data->death)
		{
			pthread_mutex_unlock(&data->death_lock);
			break ;
		}
		pthread_mutex_unlock(&data->death_lock);
	}
	return (NULL);
}


