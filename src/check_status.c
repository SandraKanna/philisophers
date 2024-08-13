/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:12:59 by sandra            #+#    #+#             */
/*   Updated: 2024/08/13 14:54:47 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_stop(t_philo *philo)
{
	pthread_mutex_lock(philo->death_lock);
	if (*philo->should_stop == 1)
	{
		pthread_mutex_unlock(philo->death_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->death_lock);
	return (0);
}

// int	meals_completed(t_data *data, t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->meals_lock);
// 	philo->meals_count++;
// 	if (philo->must_eat > 0 && philo->meals_count >= philo->must_eat)
// 	{
// 		data->all_ate++;
// 		pthread_mutex_unlock(&philo->meals_lock);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&philo->meals_lock);
// 	return (0);
// }

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;

	pthread_mutex_lock(philo->print_lock);
	timestamp = get_cur_time() - philo->start_time;
	ft_putnbr_fd(timestamp, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(status, 1);
	ft_putstr_fd("\n", 1);
	pthread_mutex_unlock(philo->print_lock);
}
