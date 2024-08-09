/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:01:51 by skanna            #+#    #+#             */
/*   Updated: 2024/08/06 15:55:49 by skanna           ###   ########.fr       */
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
			ft_putstr_fd("Parameters must be positive integers\n", 2);
			return (0);
		}
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		i;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd("Invalid number of parameters\n", 2);
		return (1);
	}
	while (av[i])
	{
		if (!check_param(av[i++]))
			return (1);
	}
	data = init_data(av);
	if (!data)
		return (1);
	if (run_philo(data) != 0)
		return (clean_struct(data), 1);
	clean_struct(data);
	return (0);
}
