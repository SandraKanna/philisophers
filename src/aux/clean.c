/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:17:03 by skanna            #+#    #+#             */
/*   Updated: 2024/08/14 23:06:38 by sandra           ###   ########.fr       */
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

void	destroy_and_free(t_data *structure, int size)
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
