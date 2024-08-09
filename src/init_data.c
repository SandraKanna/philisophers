/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:53:37 by skanna            #+#    #+#             */
/*   Updated: 2024/08/09 11:31:38 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_t	*init_philos(t_data *data)
{
	pthread_t	*philos;
	int			i;

	i = 0;
	philos = malloc (sizeof(pthread_t) * data->total_philos);
	if (!philos)
	{
		while (i < data->total_philos)
			pthread_mutex_destroy(&data->forks[i++]);
		return (free(data->forks), NULL);
	}
}

static pthread_mutex_t	*init_forks(int n_philos)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc (sizeof(pthread_mutex_t) * n_philos);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < n_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&forks[--i]);
			free(forks);
			return (1);
		}
		i++;
	}
}

t_data	*init_data(char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->total_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (!av[5])
		data->total_meals = -1;
	else
		data->total_meals = ft_atoi(av[5]);
	data->dead_flag = 0;
	data->forks = init_forks(data->total_philos);
	if (!data->forks)
		return (free(data), NULL);
	data->total_philos = init_philos(data);
	if (!data->total_philos)
		return (free(data), NULL);
	return (data);
}
