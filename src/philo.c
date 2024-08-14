/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:22:24 by skanna            #+#    #+#             */
/*   Updated: 2024/08/14 23:11:53 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	kill_philos(t_data *data, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	create_philos(t_data *data, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pthread_create(&data->philos[i].thread, NULL, \
		philo_lives, &data->philos[i]) != 0)
		{
			while (i > 0)
				pthread_detach(data->philos[--i].thread);
			return (1);
		}
		i++;
	}
	while (1)
	{
		if (monitor_end(data, size) == 1)
			break ;
		usleep_ms(2);
	}
	if (kill_philos(data, size) != 0)
		return (1);
	return (0);
}
