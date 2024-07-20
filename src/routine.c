/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:52:53 by sandra            #+#    #+#             */
/*   Updated: 2024/07/20 22:53:47 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print_lock);
	timestamp = current_timestamp() - philo->data->start_time;
	ft_putnbr_fd(timestamp, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(philo->id + 1, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(status, 1);
	ft_putstr_fd("\n", 1);
	pthread_mutex_unlock(&philo->data->print_lock);
}

static void	think(t_philo *philo)
{
	print_status(philo, "is thinking");
	usleep_ms(philo->data->time_to_eat / 2);
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
	}
	print_status(philo, "has taken a fork");
}

static void	eat(t_philo *philo)
{
	print_status(philo, "is eating");
	philo->last_meal_time = current_timestamp();
	usleep_ms(philo->data->time_to_eat);
}

static void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	print_status(philo, "has put down the forks");
}

static void	sleep_philo(t_philo *philo)
{
	print_status(philo, "is sleeping");
	usleep_ms(philo->data->time_to_sleep);
}

static int	is_dead(t_philo *philo)
{
	long long	current_time;

	current_time = current_timestamp();
	if (current_time - philo->last_meal_time > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->death_lock);
		if (!philo->data->death)
		{
			philo->data->death = 1;
			print_status(philo, "has died");
		}
		pthread_mutex_unlock(&philo->data->death_lock);
		return (1);
	}
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
		if (is_dead(philo))
			return (NULL);
		think(philo);
		if (is_dead(philo))
			return (NULL);
		take_forks(philo);
		if (is_dead(philo))
			return (NULL);
		eat(philo);
		if (is_dead(philo))
			return (NULL);
		put_forks(philo);
		if (is_dead(philo))
			return (NULL);
		sleep_philo(philo);
		if (is_dead(philo))
			return (NULL);
		pthread_mutex_lock(&data->meals_lock);
		philo->meals_count++;
		if (data->num_must_eat > 0 && philo->meals_count >= data->num_must_eat)
		{
			data->all_ate++;
			pthread_mutex_unlock(&data->meals_lock);
			break ;
		}
		pthread_mutex_unlock(&data->meals_lock);
	}
	return (NULL);
}


