/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 17:12:08 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/02 21:41:54 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "philo.h"

static int	value(int n)
{
	if (n == -1)
		return (0);
	return (-1);
}

int	ft_isspace(int c)
{
	if (c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v'
		|| c == ' ')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nbr)
{
	int		sign;
	int		i;
	long	num;
	long	max;

	i = 0;
	num = 0;
	sign = 1;
	while (ft_isspace(nbr[i]) == 1)
		i++;
	if (nbr[i] == '+' || nbr[i] == '-')
		if (nbr[i++] == '-')
			sign = -1;
	max = LONG_MAX / 10;
	while (ft_isdigit(nbr[i]) == 1)
	{
		if (num > max)
			return (value(sign));
		num = (num * 10) + (nbr[i] - '0');
		if (num < 0)
			return (value(sign));
		i++;
	}
	return ((int)(num * sign));
}

char	*ft_strncpy(char *src, char *dst, int n)
{
	int		i;
	int		j;
	char	size[255];

	j = 0;
	while (src[j] != '\0')
	{
		dst[j] = src[j];
		j++;
	}
	i = 0;
	while (n > 0)
	{
		size[i++] = (n % 10) + '0';
		n = n / 10;
	}
	while (i > 0)
	{
		dst[j] = size[--i];
		j++;
	}
	dst[j] = '\0';
	return (dst);
}
