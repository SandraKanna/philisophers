/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:11:59 by derjavec          #+#    #+#             */
/*   Updated: 2024/08/07 13:26:11 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_rules *rules, int id, char *str)
{
	pthread_mutex_lock(&(rules->writing));
	pthread_mutex_lock(&(rules->dead_check));
	if (rules->dead == 0)
	{
		printf("%lli ", timestamp() - rules->first_timestamp);
		printf("%i ", id);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(rules->dead_check));
	pthread_mutex_unlock(&(rules->writing));
	return ;
}
