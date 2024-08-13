/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_rutine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:52:54 by derjavec          #+#    #+#             */
/*   Updated: 2024/08/12 11:31:32 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait(long long time, t_rules *rules)
{
	long long	start_time;
	long long	current_time;

	start_time = timestamp();
	while (1)
	{
		pthread_mutex_lock(&(rules->dead_check));
		if (rules->dead != 0)
		{
			pthread_mutex_unlock(&(rules->dead_check));
			return ;
		}
		pthread_mutex_unlock(&(rules->dead_check));
		current_time = timestamp();
		if (current_time - start_time >= time)
			break ;
		usleep(50);
	}
}

static void	one_philo_case(t_philosopher *phi, t_rules *rules)
{
	pthread_mutex_lock(&(rules->forks[phi->left_fork_id]));
	print_action(rules, phi->id, "has taken left fork");
	wait(rules->time_until_death, rules);
	pthread_mutex_unlock(&(rules->forks[phi->left_fork_id]));
}

static void	philo_eats(t_rules *rules, t_philosopher *phi)
{
	if (rules->philo_quantity == 1)
		return (one_philo_case(phi, rules));
	pthread_mutex_lock(&(rules->forks[phi->left_fork_id]));
	print_action(rules, phi->id, "has taken left fork");
	pthread_mutex_lock(&(rules->forks[phi->right_fork_id]));
	print_action(rules, phi->id, "has taken right fork");
	pthread_mutex_lock(&(rules->dead_check));
	if (rules->dead != 0)
	{
		pthread_mutex_unlock(&(rules->dead_check));
		pthread_mutex_unlock(&(rules->forks[phi->left_fork_id]));
		pthread_mutex_unlock(&(rules->forks[phi->right_fork_id]));
		return ;
	}
	pthread_mutex_unlock(&(rules->dead_check));
	pthread_mutex_lock(&(rules->meal_check));
	phi->t_last_meal = timestamp() - rules->first_timestamp;
	print_action(rules, phi->id, "is eating");
	pthread_mutex_unlock(&(rules->meal_check));
	wait(rules->time_to_eat, rules);
	pthread_mutex_lock(&(rules->ate_check));
	(phi->x_ate)++;
	pthread_mutex_unlock(&(rules->ate_check));
	pthread_mutex_unlock(&(rules->forks[phi->left_fork_id]));
	pthread_mutex_unlock(&(rules->forks[phi->right_fork_id]));
}

static int	eat_sleep_and_think(t_rules *rules, t_philosopher *phi)
{
	philo_eats(rules, phi);
	if (rules->full_philo_quantity != 0 && \
		phi->x_ate == rules->full_philo_quantity)
		return (1);
	if (rules->philo_quantity > 1)
		print_action(rules, phi->id, "is sleeping");
	wait(rules->time_to_sleep, rules);
	if (rules->philo_quantity > 1)
		print_action(rules, phi->id, "is thinking");
	return (0);
}

void	*philosopher_rutine(void *void_phi)
{
	t_philosopher	*phi;
	t_rules			*rules;

	phi = (t_philosopher *)void_phi;
	rules = phi->rules;
	if (phi->id % 2 == 0 || phi->id == rules->philo_quantity)
		wait(rules->time_to_eat, rules);
	while (1)
	{
		pthread_mutex_lock(&(rules->dead_check));
		if (rules->dead != 0)
		{
			pthread_mutex_unlock(&(rules->dead_check));
			break ;
		}
		pthread_mutex_unlock(&(rules->dead_check));
		if (eat_sleep_and_think(rules, phi) == 1)
			break ;
	}
	return (NULL);
}
