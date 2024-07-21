/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:22:24 by skanna            #+#    #+#             */
/*   Updated: 2024/07/21 17:03:49 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philos(t_data *structure, int size)
{
	int				i;
	pthread_mutex_t	*forks;

	structure->philos = malloc(sizeof(t_philo) * size);
	if (!structure->philos)
		return (1);
	i = 0;
	forks = structure->forks;
	while (i < size)
	{
		structure->philos[i].id = i + 1;
		structure->philos[i].last_meal_time = current_timestamp();
		structure->philos[i].meals_count = 0;
		structure->philos[i].left_fork = &forks[i];
		structure->philos[i].right_fork = &forks[(i + 1) % size];
		structure->philos[i].data = structure;
		i++;
	}
	return (0);
}

static int	init_forks(t_data *structure, int size)
{
	int	i;

	structure->forks = malloc(sizeof(pthread_mutex_t) * size);
	if (!structure->forks)
		return (1);
	i = 0;
	while (i < size)
	{
		if (pthread_mutex_init(&structure->forks[i], NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&structure->forks[--i]);
			free(structure->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_mutexes(t_data *structure)
{
	if (pthread_mutex_init(&structure->print_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&structure->meals_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&structure->print_lock);
		return (1);
	}
	if (pthread_mutex_init(&structure->death_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&structure->print_lock);
		pthread_mutex_destroy(&structure->meals_lock);
		return (1);
	}
	if (init_forks(structure, structure->num_philo) == 1)
	{
		pthread_mutex_destroy(&structure->print_lock);
		pthread_mutex_destroy(&structure->meals_lock);
		pthread_mutex_destroy(&structure->death_lock);
		return (1);
	}
	return (0);
}

t_data	*init_struct(char **av)
{
	t_data			*structure;
	int				err;

	structure = malloc (sizeof (t_data));
	if (!structure)
		return (NULL);
	ft_memset(structure, '\0', sizeof (t_data));
	err = 0;
	structure->num_philo = ft_atoll(av[1], &err);
	structure->time_to_die = ft_atoll(av[2], &err);
	structure->time_to_eat = ft_atoll(av[3], &err);
	structure->time_to_sleep = ft_atoll(av[4], &err);
	if (av[5])
		structure->num_must_eat = ft_atoll(av[5], &err);
	if (err)
		return (free(structure), NULL);
	structure->start_time = current_timestamp();
	if (init_mutexes(structure) != 0)
		return (free(structure), NULL);
	if (init_philos(structure, structure->num_philo) != 0)
		return (free(structure->forks), free(structure), NULL);
	return (structure);
}
