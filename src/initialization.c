/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:22:24 by skanna            #+#    #+#             */
/*   Updated: 2024/08/12 13:14:13 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_args(t_philo *philo, int size, char **av)
{
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (!av[5])
		philo->must_eat = -1;
	else
		philo->must_eat = ft_atoi(av[5]);
	philo->start_time = get_cur_time();
	philo->last_meal = get_cur_time();
	philo->is_dead = 0;
	philo->is_eating = 0;
	philo->meals_count = 0;
}

static void	init_philos(t_data *data, int size, char **args)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = data->forks;
	while (i < size)
	{
		data->philos[i].id = i + 1;
		init_args(&data->philos[i], size, args);
		data->philos[i].l_fork = &data->forks[i];
		if (i == 0)
			data->philos[i].l_fork = &data->forks[size - 1];
		else
			data->philos[i].l_fork = &data->forks[i - 1];
		data->philos[i].death_lock = &data->death_lock;
		data->philos[i].meals_lock = &data->meals_lock;
		data->philos[i].print_lock = &data->print_lock;
		i++;
	}
}

static int	init_forks(t_data *structure, int size)
{
	int	i;

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

static int	init_mutexes(t_data *structure, int size)
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
	return (0);
}

t_data	*init_struct(char **av)
{
	t_data			*data;
	int				size;

	data = malloc (sizeof (t_data));
	if (!data)
		return (NULL);
	data->dead_flag = 0;
	size = ft_atoi(av[1]);
	data->philos = malloc(sizeof(t_philo) * size);
	if (!data->philos)
		return (free(data), NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * size);
	if (!data->forks)
		return (free(data->philos), free(data), NULL);
	if (init_forks(data, size) != 0)
		return (free(data->philos), free(data->forks), free(data), NULL);
	if (init_mutexes(data, size) != 0)
		return (free(data->philos), free(data->forks), free(data), NULL);
	init_philos(data, size, av);
	return (data);
}
