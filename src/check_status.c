/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:12:59 by sandra            #+#    #+#             */
/*   Updated: 2024/07/21 17:02:18 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
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

int	meals_completed(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->meals_lock);
	philo->meals_count++;
	if (data->num_must_eat > 0 && philo->meals_count >= data->num_must_eat)
	{
		data->all_ate++;
		pthread_mutex_unlock(&data->meals_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->meals_lock);
	return (0);
}

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print_lock);
	timestamp = current_timestamp() - philo->data->start_time;
	ft_putnbr_fd(timestamp, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(status, 1);
	ft_putstr_fd("\n", 1);
	pthread_mutex_unlock(&philo->data->print_lock);
}
