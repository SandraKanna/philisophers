/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:22:24 by skanna            #+#    #+#             */
/*   Updated: 2024/08/12 19:11:45 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static int	monitor_end(t_data *structure)
// {
// 	if (structure->all_ate == structure->num_philo)
// 	{
// 		pthread_mutex_unlock(&structure->death_lock);
// 		pthread_mutex_unlock(&structure->meals_lock);
// 		ft_putstr_fd("All philosophers have eaten.\n", 1);
// 		return (1);
// 	}
// 	if (structure->death)
// 	{
// 		pthread_mutex_unlock(&structure->death_lock);
// 		pthread_mutex_unlock(&structure->meals_lock);
// 		ft_putstr_fd("A philosopher has died.\n", 1);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&structure->death_lock);
// 	pthread_mutex_unlock(&structure->meals_lock);
// 	usleep(1000);
// 	return (0);
// }

// static int	wait_and_terminate(t_data *structure)
// {
// 	int	i;

// 	i = 0;
// 	while (i < structure->num_philo)
// 	{
// 		if (pthread_join(structure->philos[i].thread, NULL) != 0)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

int	run_philo(t_data *structure, int size)
{
	int	i;

	i = 0;
	// structure->start_time = current_timestamp();
	//whatcher aveec thread -> remplace boucle monitor_end
	while (i < size)
	{
		if (pthread_create(&structure->philos[i].thread, NULL, \
		routine, &structure->philos[i]) != 0)
		{
			while (i > 0)
				pthread_detach(structure->philos[--i].thread);
			return (1);
		}
		i++;
	}
	while (1)
	{
		if (monitor_end(structure) != 0)
			break ;
	}
	if (wait_and_terminate(structure) != 0)
		return (1);
	return (0);
}




// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg); 