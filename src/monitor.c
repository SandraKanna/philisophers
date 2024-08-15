/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:12:59 by sandra            #+#    #+#             */
/*   Updated: 2024/08/15 15:25:17 by skanna           ###   ########.fr       */
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

static int	check_death(t_data *data, int size, int i)
{
	long long	cur_time;

	while (i < size)
	{
		cur_time = get_cur_time();
		pthread_mutex_lock(&data->meals_lock);
		pthread_mutex_lock(&data->print_lock);
		if (!data->philos[i].is_eating && cur_time \
		- data->philos[i].last_meal > data->philos[i].time_to_die)
		{
			pthread_mutex_lock(&data->death_lock);
			data->stop = 1;
			pthread_mutex_unlock(&data->death_lock);
			printf("%llu Philosopher %d has died\n", cur_time - \
			data->philos[i].last_meal, data->philos[i].id);
			pthread_mutex_unlock(&data->print_lock);
			pthread_mutex_unlock(&data->meals_lock);
			kill_zombies(data, size);
			return (destroy_mutex(data, size), 1);
		}
		pthread_mutex_unlock(&data->print_lock);
		pthread_mutex_unlock(&data->meals_lock);
		i++;
	}
	return (0);
}

static void	all_have_eaten(t_data *data, int size)
{
	pthread_mutex_lock(&data->death_lock);
	data->stop = 1;
	pthread_mutex_unlock(&data->death_lock);
	pthread_mutex_lock(&data->print_lock);
	printf("All have eaten\n");
	pthread_mutex_unlock(&data->print_lock);
	kill_zombies(data, size);
	destroy_mutex(data, size);
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
		return (all_have_eaten(data, size), 1);
	return (0);
}

void	monitor_end(t_data *data, int size)
{
	int	i;

	i = 0;
	while (1)
	{
		if (check_death(data, size, i) != 0 || check_meals(data, size) != 0)
			break ;
		usleep_ms(1);
	}
}
