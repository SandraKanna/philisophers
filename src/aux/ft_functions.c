/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:32:01 by skanna            #+#    #+#             */
/*   Updated: 2024/08/14 23:13:00 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*string1;
	unsigned char	*string2;
	int				i;

	string1 = (unsigned char *)s1;
	string2 = (unsigned char *)s2;
	i = 0;
	while (string1[i] || string2[i])
	{
		if (string1[i] != string2[i])
			return (string1[i] - string2[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	ft_isdigit(int d)
{
	if (d >= 48 && d <= 57)
		return (1);
	return (0);
}

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
