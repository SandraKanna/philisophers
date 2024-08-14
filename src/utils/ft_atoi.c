/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:54:39 by skanna            #+#    #+#             */
/*   Updated: 2024/08/14 15:13:25 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int d)
{
	if (d >= 48 && d <= 57)
		return (1);
	return (0);
}

// static int	atoll_helper(const char *str, int *sign)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
// 		i++;
// 	if (str[i] == '-' || str[i] == '+')
// 	{
// 		if (str[i] == '-')
// 			*sign = -1;
// 		i++;
// 	}
// 	return (i);
// }

// long long	ft_atoll(const char *str, int *err)
// {
// 	long long	result;
// 	int			sign;
// 	int			i;

// 	result = 0;
// 	sign = 1;
// 	i = atoll_helper(str, &sign);
// 	while (ft_isdigit(str[i]))
// 	{
// 		if (result > (LLONG_MAX - (str[i] - '0')) / 10)
// 		{
// 			*err = 1;
// 			return (0);
// 		}
// 		result = result * 10 + (str[i] - '0');
// 		i++;
// 	}
// 	while (str[i] == ' ')
// 		i++;
// 	if (str[i] != '\0')
// 		*err = 1;
// 	return (result * sign);
// }

static int	count_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			break ;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	long	num;
	int		sign;
	int		i;
	int		n;

	num = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 45)
		sign = -1;
	if (*str == 43 || *str == 45)
		str++;
	n = count_digits((char *)str);
	i = 0;
	while (i < n)
	{
		num = (num * 10) + (str[i] - '0');
		if ((sign == 1 && num > INT_MAX) || (sign == -1 && (-num) < INT_MIN))
			return (0);
		i++;
	}
	return ((long long)(num * sign));
}
