/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:43:58 by skanna            #+#    #+#             */
/*   Updated: 2024/07/21 14:38:53 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		write(fd, &(s[i++]), 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	nbr;
	char		c;

	nbr = n;
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr = nbr * -1;
	}
	if (nbr < 10)
	{
		c = nbr + 48;
		write(fd, &c, 1);
	}
	else
	{
		ft_putnbr_fd((nbr / 10), fd);
		c = nbr % 10 + 48;
		write(fd, &c, 1);
	}
}

void	*ft_memset(void *arg, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((char *)arg)[i++] = c;
	return (arg);
}

long long	current_timestamp(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
		ft_putstr_fd("Error getting time of day\n", 2);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	usleep_ms(int ms)
{
	usleep(ms * 1000);
}
