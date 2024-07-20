/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:52:53 by sandra            #+#    #+#             */
/*   Updated: 2024/07/20 21:20:38 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void think(t_philo *philo)
{
    print_status(philo, "is thinking");
    usleep_ms(philo->data->time_to_eat / 2); // Example sleep duration
}

static void take_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    print_status(philo, "has taken a fork");
}

static void eat(t_philo *philo)
{
    print_status(philo, "is eating");
    philo->last_meal_time = current_timestamp();
    usleep_ms(philo->data->time_to_eat);
}

static void put_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
    print_status(philo, "has put down the forks");
}

static void sleep_philo(t_philo *philo)
{
    print_status(philo, "is sleeping");
    usleep_ms(philo->data->time_to_sleep);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		think(philo);
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		sleep_philo(philo);
	}
	return (NULL);
}
