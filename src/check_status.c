/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:12:59 by sandra            #+#    #+#             */
/*   Updated: 2024/08/14 16:29:20 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_stop(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(&philo->data->death_lock);
	stop = philo->data->stop;
	pthread_mutex_unlock(&philo->data->death_lock);

	return (stop);
}

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;

	// if (should_stop(philo) != 0)
	// 	return ;
	timestamp = 0;
	pthread_mutex_lock(&philo->data->print_lock);
	// timestamp = get_cur_time() - philo->start_time;
	// ft_putnbr_fd(timestamp, 1);
	// ft_putstr_fd(" ", 1);
	// ft_putnbr_fd(philo->id, 1);
	// ft_putstr_fd(" ", 1);
	// ft_putstr_fd(status, 1);
	// ft_putstr_fd("\n", 1);
	if (!should_stop(philo))
		printf("%llu %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_lock);
}
