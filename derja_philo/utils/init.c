/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:23:59 by derjavec          #+#    #+#             */
/*   Updated: 2024/08/08 13:19:13 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_mutex(t_rules *rules)
{
	int	i;

	pthread_mutex_init(&(rules->meal_check), NULL);
	pthread_mutex_init(&(rules->writing), NULL);
	pthread_mutex_init(&(rules->dead_check), NULL);
	pthread_mutex_init(&(rules->ate_check), NULL);
	i = 1;
	while (i <= rules->philo_quantity)
	{
		pthread_mutex_init(&(rules->forks[i]), NULL);
		i++;
	}
}

void	init(t_rules *rules, int *data)
{
	rules->phi = malloc((data[0] + 1) * sizeof(t_philosopher));
	if (!rules->phi)
		return (ft_error("Malloc error in init function", rules));
	rules->forks = malloc((data[0] + 1) * sizeof(pthread_mutex_t));
	if (!rules->forks)
		return (ft_error("Malloc error in init function", rules));
	rules->philo_quantity = data[0];
	rules->time_until_death = data[1];
	rules->time_to_eat = data[2];
	rules->time_to_sleep = data[3];
	rules->full_philo_quantity = data[4];
	rules->philo_ate_all = 0;
	rules->dead = 0;
	rules->first_timestamp = timestamp();
	init_mutex(rules);
}
