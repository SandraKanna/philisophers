/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:12:59 by sandra            #+#    #+#             */
/*   Updated: 2024/08/14 17:03:08 by skanna           ###   ########.fr       */
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

	if (should_stop(philo))
		return ;
	timestamp = get_cur_time() - philo->start_time;
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%llu %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_lock);
}
