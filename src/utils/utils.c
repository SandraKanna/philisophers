/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:43:58 by skanna            #+#    #+#             */
/*   Updated: 2024/08/13 14:45:02 by skanna           ###   ########.fr       */
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

long long	get_cur_time(void)
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
