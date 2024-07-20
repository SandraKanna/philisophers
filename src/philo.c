/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:22:24 by skanna            #+#    #+#             */
/*   Updated: 2024/07/20 20:59:51 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	usleep_ms(int ms)
{
	usleep(ms * 1000);
}

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print_lock);
	timestamp = current_timestamp() - philo->data->start_time;
	ft_putnbr_fd(timestamp, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(philo->id + 1, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(status, 1);
	ft_putstr_fd("\n", 1);
	pthread_mutex_unlock(&philo->data->print_lock);
}

int	run_philo(t_data *structure)
{
	int	i;

	i = 0;
	while (i < structure->num_philo)
	{
		if (pthread_create(&structure->philos[i].thread, NULL, routine, &structure->philos[i]) != 0)
		{
			while (i > 0)
				pthread_detach(structure->philos[--i].thread);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < structure->num_philo)
	{
		if (pthread_join(structure->philos[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}




// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg); 