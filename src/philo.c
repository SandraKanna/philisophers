/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:22:24 by skanna            #+#    #+#             */
/*   Updated: 2024/08/13 15:55:14 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_data *data, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		// printf("check death: %d\n", i);
		pthread_mutex_lock(data->philos[i].meals_lock);
		if (get_cur_time() - data->philos[i].last_meal > \
		data->philos[i].time_to_die && data->philos[i].is_eating != 0)
		{
			pthread_mutex_unlock(data->philos[i].meals_lock);
			pthread_mutex_lock(data->philos[i].death_lock);
			*data->philos[i].should_stop = 1;
			print_status(&data->philos[i], "has died");
			pthread_mutex_unlock(data->philos[i].death_lock);
			// return (clean_struct(data, size), 1);
			return (1);
		}
		pthread_mutex_unlock(data->philos[i].meals_lock);
		i++;
	}
	return (0);
}

static int	check_all_ate(t_data *data, int size)
{
	int	i;

	i = 0;
	pthread_mutex_lock(data->philos[i].meals_lock);
	if (data->philos[i].must_eat == 0)
		return (pthread_mutex_unlock(data->philos[i].meals_lock), 0);
	pthread_mutex_unlock(data->philos[i].meals_lock);
	while (i < size)
	{
		pthread_mutex_lock(data->philos[i].meals_lock);
		if (data->philos[i].meals_count == data->philos[i].must_eat)
			data->all_ate++;
		pthread_mutex_unlock(data->philos[i].meals_lock);
		i++;
	}
	pthread_mutex_lock(&data->meals_lock);
	if (data->all_ate == data->philos[0].must_eat)
	{
		pthread_mutex_unlock(&data->meals_lock);
		pthread_mutex_lock(&data->death_lock);
		data->stop = 1;
		pthread_mutex_unlock(&data->death_lock);
		pthread_mutex_lock(&data->print_lock);
		ft_putstr_fd("All have eaten\n", 1);
		pthread_mutex_unlock(&data->print_lock);
		// return (clean_struct(data, size), 1);
		return (1);
	}
	pthread_mutex_unlock(&data->meals_lock);
	return (0);
}

static int	wait_and_terminate(t_data *data, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	run_philo(t_data *data, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pthread_create(&data->philos[i].thread, NULL, \
		routine, &data->philos[i]) != 0)
		{
			while (i > 0)
				pthread_detach(data->philos[--i].thread);
			return (1);
		}
		i++;
	}
	while (1)
	{
		// printf("stop flag: %d\n", data->stop);
		if (check_death(data, size) != 0 || check_all_ate(data, size) != 0)
			break ;
	}
	if (wait_and_terminate(data, size) != 0)
		return (1);
	return (0);
}




// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg); 