/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:20:38 by derjavec          #+#    #+#             */
/*   Updated: 2023/10/20 11:20:42 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static const char	*erase_spaces(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (str + i);
}

static const char	*erase_sign(const char *str)
{
	if (str[0] == '-' || str[0] == '+')
		return (str + 1);
	else
		return (str);
}

int	ft_atoi(const char *str, t_rules *rules)
{
	int	c;
	int	i;
	int	sign;

	str = erase_spaces(str);
	sign = 1;
	if (str[0] == '-')
		sign = -1;
	str = erase_sign(str);
	if (str[0] > '9' || str[0] < '0')
		ft_error("One or more not int arguments found", rules);
	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			c = c * 10 + str[i] - 48;
		else
			break ;
		i++;
	}
	return (c * sign);
}
