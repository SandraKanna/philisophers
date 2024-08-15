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
			while (i > 0)
				pthread_detach(data->philos[--i].thread);
			return (1);
		}
		i++;
	}
	return (0);
}
