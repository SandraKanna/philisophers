/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:12:59 by sandra            #+#    #+#             */
/*   Updated: 2024/08/14 23:13:47 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_stop(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(&philo->data->death_lock);
	stop = philo->data->stop;
	pthread_mutex_unlock(&philo->data->death_lock);
	return (stop);
}

static int	check_death(t_data *data, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_lock(&data->meals_lock);
		if (!data->philos[i].is_eating && get_cur_time() \
		- data->philos[i].last_meal > data->philos[i].time_to_die)
		{
			pthread_mutex_unlock(&data->meals_lock);
			print_status(&data->philos[i], "has died");
			pthread_mutex_lock(&data->death_lock);
			data->stop = 1;
			pthread_mutex_unlock(&data->death_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->meals_lock);
		i++;
	}
	return (0);
}

static void	all_have_eaten(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	data->stop = 1;
	pthread_mutex_unlock(&data->death_lock);
	pthread_mutex_lock(&data->print_lock);
	printf("All have eaten\n");
	pthread_mutex_unlock(&data->print_lock);
}

static int	check_meals(t_data *data, int size)
{
	int	i;
	int	all_ate;

	i = 0;
	all_ate = 0;
	pthread_mutex_lock(&data->meals_lock);
	if (data->philos[0].must_eat == -1)
		return (pthread_mutex_unlock(&data->meals_lock), 0);
	pthread_mutex_unlock(&data->meals_lock);
	while (i < size)
	{
		pthread_mutex_lock(&data->meals_lock);
		if (data->philos[i].meals_count >= data->philos[i].must_eat)
			all_ate++;
		pthread_mutex_unlock(&data->meals_lock);
		i++;
	}
	if (all_ate == size)
		return (all_have_eaten(data), 1);
	return (0);
}

int	monitor_end(t_data *data, int size)
{
	if (check_death(data, size) != 0 || check_meals(data, size) != 0)
		return (1);
	return (0);
}
