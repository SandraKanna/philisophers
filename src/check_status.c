/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:12:59 by sandra            #+#    #+#             */
/*   Updated: 2024/08/13 11:43:05 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	long long	current_time;

	current_time = get_cur_time();
	if (current_time - philo->last_meal > philo->time_to_die)
	{
		pthread_mutex_lock(&philo->death_lock);
		if (!philo->stop)
		{
			philo->stop = 1;
			print_status(philo, "has died");
		}
		pthread_mutex_unlock(&philo->death_lock);
		return (1);
	}
	return (0);
}

int	meals_completed(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_lock);
	philo->meals_count++;
	if (philo->must_eat > 0 && philo->meals_count >= philo->must_eat)
	{
		data->all_ate++;
		pthread_mutex_unlock(&philo->meals_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meals_lock);
	return (0);
}

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->print_lock);
	timestamp = get_cur_time() - philo->start_time;
	ft_putnbr_fd(timestamp, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(status, 1);
	ft_putstr_fd("\n", 1);
	pthread_mutex_unlock(&philo->print_lock);
}
