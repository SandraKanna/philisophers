/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:43:58 by skanna            #+#    #+#             */
/*   Updated: 2024/08/15 14:24:24 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_cur_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
		err_msg("Error getting time of day");
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	usleep_ms(long long sleep)
{
	long long	start;
	long long	cur;

	start = get_cur_time();
	cur = start;
	while (cur - start < sleep)
	{
		usleep(1);
		cur = get_cur_time();
	}
}

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;

	timestamp = get_cur_time() - philo->start_time;
	pthread_mutex_lock(&philo->data->print_lock);
	if (!should_stop(philo))
		printf("%lld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_lock);
}
