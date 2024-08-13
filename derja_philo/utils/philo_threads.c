/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:02:43 by derjavec          #+#    #+#             */
/*   Updated: 2024/08/08 09:38:22 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_threads(t_rules *rules)
{
	int	i;

	i = 1;
	while (i <= rules->philo_quantity)
	{
		rules->phi[i].id = i;
		rules->phi[i].x_ate = 0;
		rules->phi[i].left_fork_id = i;
		rules->phi[i].right_fork_id = (i + 1) % rules->philo_quantity;
		if (rules->phi[i].right_fork_id == 0)
			rules->phi[i].right_fork_id = rules->philo_quantity;
		rules->phi[i].t_last_meal = 0;
		rules->phi[i].rules = rules;
		rules->phi[i].thread_id = 0;
		if (pthread_create(&(rules->phi[i].thread_id), NULL, \
			philosopher_rutine, &(rules->phi[i])) != 0)
		{
			rules->philo_quantity = i;
			clean_threads(rules, rules->phi);
			ft_error("Error creating thread", rules);
		}			
		i++;
	}
}
