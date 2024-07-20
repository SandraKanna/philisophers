/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:01:51 by skanna            #+#    #+#             */
/*   Updated: 2024/07/20 16:23:16 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_param(char *str)
{
	int	i;

	i = 0;
	if (str[0] == 48 && str[1] == '\0')
	{
		ft_putstr_fd("Parameters should be bigger than zero\n", 2);
		return (0);
	}
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
			i++;
		else
		{
			ft_putstr_fd("Wrong type of parameter\n", 2);
			return (0);
		}
	}
	return (1);
}

t_philo	*init_philo(char **av)
{
	t_philo	*params;
	int		err;

	params = malloc (sizeof (t_philo));
	if (!params)
		return (NULL);
	err = 0;
	params->num_philo = ft_atoll(av[1], &err);
	params->time_to_die = ft_atoll(av[2], &err);
	params->time_to_eat = ft_atoll(av[3], &err);
	params->time_to_sleep = ft_atoll(av[4], &err);
	if (av[5])
		params->num_must_eat = ft_atoll(av[5], &err);
	else
		params->num_must_eat = 0;
	if (err)
		return (NULL);
	return (params);
}

int	main(int ac, char **av)
{
	t_philo	*params;
	int		i;

	i = 1;
	if (ac >= 5 && ac <= 6)
	{
		while (av[i])
		{
			if (!check_param(av[i++]))
				return (1);
		}
	}
	else
	{
		ft_putstr_fd("Wrong number of parameters\n", 2);
		return (1);
	}
	params = init_philo(av);
	if (!params)
		return (1);
	run_philo(params);
	return (0);
}
