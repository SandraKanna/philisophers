/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:17:03 by skanna            #+#    #+#             */
/*   Updated: 2024/08/15 15:15:02 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		write(fd, &(s[i++]), 1);
}

void	err_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	kill_zombies(t_data *data, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			err_msg("Error joining threads");
		i++;
	}
}

void	destroy_mutex(t_data *structure, int size)
{
	int	i;

	i = 0;
	if (structure->forks)
	{
		while (i < size)
			pthread_mutex_destroy(&structure->forks[i++]);
	}
	pthread_mutex_destroy(&structure->print_lock);
	pthread_mutex_destroy(&structure->meals_lock);
	pthread_mutex_destroy(&structure->death_lock);
}

void	free_data(t_data *structure)
{
	if (structure->forks)
		free(structure->forks);
	if (structure->philos)
		free(structure->philos);
	free(structure);
}
