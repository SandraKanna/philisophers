/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:17:03 by skanna            #+#    #+#             */
/*   Updated: 2024/07/21 17:02:42 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_struct(t_data *structure)
{
	int	i;

	i = 0;
	if (structure->forks)
	{
		while (i < structure->num_philo)
			pthread_mutex_destroy(&structure->forks[i++]);
		free(structure->forks);
	}
	if (structure->philos)
	{
		// i = 0;
		// while (i < structure->num_philo)
		// 	pthread_mutex_destroy(&structure->philos[i++].last_meal_time_lock);
		free(structure->philos);
	}
	pthread_mutex_destroy(&structure->print_lock);
	pthread_mutex_destroy(&structure->meals_lock);
	pthread_mutex_destroy(&structure->death_lock);
	free(structure);
}
