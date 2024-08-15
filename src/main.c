/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:01:51 by skanna            #+#    #+#             */
/*   Updated: 2024/08/15 15:25:45 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_int_limits(char *str)
{
	char	*int_max;
	char	*int_min;

	int_max = "2147483647";
	int_min = "2147483648";
	if (ft_strlen(str) > 10)
		return (err_msg("Parameters must be within integer range"), 0);
	else if (ft_strlen(str) == 10)
	{
		if (str[0] == '-')
		{
			if (ft_strcmp(&str[1], int_min) > 0)
				return (err_msg("Parameters must be within integer range"), 0);
		}
		else if (ft_strcmp(str, int_max) > 0)
			return (err_msg("Parameters must be within integer range"), 0);
	}
	return (1);
}

static int	check_param(char *str)
{
	int		i;

	i = 0;
	if (str[0] == 48 && str[1] == '\0')
		return (err_msg("Parameters should be bigger than zero"), 0);
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
			i++;
		else
			return (err_msg("Parameters must be positive integers"), 0);
	}
	if (!check_int_limits(str))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		i;

	i = 1;
	if (ac != 5 && ac != 6)
		return (err_msg("Invalid number of parameters"), 1);
	while (av[i])
	{
		if (!check_param(av[i++]))
			return (1);
	}
	data = initialize(av);
	if (!data)
		return (1);
	if (create_philos(data, ft_atoi(av[1])) != 0)
		return (free_data(data), 1);
	monitor_end(data, ft_atoi(av[1]));
	free_data(data);
	return (0);
}
