/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:01:51 by skanna            #+#    #+#             */
/*   Updated: 2024/07/20 21:26:35 by sandra           ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_data	*structure;
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
	structure = init_struct(av);
	if (!structure)
		return (1);
	if (run_philo(structure) != 0)
		return (clean_struct(structure), 1);
	clean_struct(structure);
	return (0);
}
