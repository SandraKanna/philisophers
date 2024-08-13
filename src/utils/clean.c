/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:17:03 by skanna            #+#    #+#             */
/*   Updated: 2024/08/13 16:01:26 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_struct(t_data *structure, int size)
{
	int	i;

	i = 0;
	if (!structure)
		return ;
	if (structure->forks)
	{
		while (i < size)
			pthread_mutex_destroy(&structure->forks[i++]);
		free(structure->forks);
	}
	if (structure->philos)
	{
		free(structure->philos);
	}
	pthread_mutex_destroy(&structure->print_lock);
	pthread_mutex_destroy(&structure->meals_lock);
	pthread_mutex_destroy(&structure->death_lock);
	free(structure);
	structure = NULL;
}
