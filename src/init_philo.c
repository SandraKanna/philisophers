/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:22:24 by skanna            #+#    #+#             */
/*   Updated: 2024/07/20 22:35:32 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *structure, int size)
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
			structure->forks = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_philos(t_data *structure, int size)
{
	int				i;
	pthread_mutex_t	*forks;
	long long		current_time;

	structure->philos = malloc(sizeof(t_philo) * size);
	if (!structure->philos)
		return (1);
	i = 0;
	current_time = current_timestamp();
	forks = structure->forks;
	while (i < size)
	{
		structure->philos[i].id = i;
		structure->philos[i].last_meal_time = current_time;
		structure->philos[i].left_fork = &forks[i];
		structure->philos[i].right_fork = &forks[(i + 1) % size];
		structure->philos[i].data = structure;
		i++;
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
	else
		structure->num_must_eat = 0;
	if (err)
		return (free(structure), NULL);
	if (pthread_mutex_init(&structure->print_lock, NULL) != 0)
		return (free(structure), NULL);
	if (pthread_mutex_init(&structure->meals_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&structure->print_lock);
		return (free(structure), NULL);
	}
	if (pthread_mutex_init(&structure->death_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&structure->print_lock);
		pthread_mutex_destroy(&structure->meals_lock);
		return (free(structure), NULL);
	}
	structure->death = 0;
	if (init_forks(structure, structure->num_philo) == 1)
		return (pthread_mutex_destroy(&structure->print_lock), free(structure), NULL);
	if (init_philos(structure, structure->num_philo) == 1)
		return (clean_struct(structure), NULL);
	structure->start_time = current_timestamp();
	return (structure);
}
