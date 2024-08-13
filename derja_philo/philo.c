/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:00:44 by derjavec          #+#    #+#             */
/*   Updated: 2024/08/08 09:32:01 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	fill_data_array(int argc, char *argv[], int *data, t_rules *rules)
{
	int	i;

	if (argc < 5 || argc > 6)
		ft_error("Wrong number of arguments", rules);
	i = 0;
	while (i < argc - 1)
	{
		data[i] = ft_atoi(argv[i + 1], rules);
		if (data[i] < 0 || (data == 0 && i < 5))
			ft_error("One or more zero or negative arguments found", rules);
		i++;
	}
	if (i == 4)
		data[4] = 0;
	return ;
}

int	main(int argc, char *argv[])
{
	int		data[5];
	t_rules	*rules;

	rules = malloc(sizeof(t_rules));
	if (rules == NULL)
		ft_error("Malloc error in main function", rules);
	fill_data_array(argc, argv, data, rules);
	init(rules, data);
	philo_threads(rules);
	check_if_philo_died(rules);
	clean_threads(rules, rules->phi);
	free(rules->forks);
	free(rules->phi);
	free(rules);
	return (0);
}
