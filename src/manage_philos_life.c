/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_philos_life.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:22:24 by skanna            #+#    #+#             */
/*   Updated: 2024/08/15 15:32:16 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	manage_philos(t_data *data, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pthread_create(&data->philos[i].thread, NULL, \
		philo_lives, &data->philos[i]) != 0)
		{
			/* Philos 0 to i-1 are already running and using *data:
			tell them to stop, wait for them (join), only then clean up.
			Freeing *data while they run would be a use-after-free. */
			pthread_mutex_lock(&data->death_lock);
			data->stop = 1;
			pthread_mutex_unlock(&data->death_lock);
			kill_zombies(data, i);
			err_msg("Error creating thread");
			return (1);
		}
		i++;
	}
	return (0);
}
