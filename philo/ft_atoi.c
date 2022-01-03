/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 17:12:08 by ktiong            #+#    #+#             */
/*   Updated: 2021/04/30 17:12:08 by ktiong           ###   ########.fr       */
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

int	ft_atoi(const char *thread_num)
{
	int		sign;
	int		i;
	long	num;
	long	max;

	i = 0;
	num = 0;
	sign = 1;
	while (ft_isspace(thread_num[i]) == 1)
		i++;
	if (thread_num[i] == '+' || thread_num[i] == '-')
		if (thread_num[i++] == '-')
			sign = -1;
	max = LONG_MAX / 10;
	while (ft_isdigit(thread_num[i]) == 1)
	{
		if (num > max)
			return (value(sign));
		num = (num * 10) + (thread_num[i] - '0');
		if (num < 0)
			return (value(sign));
		i++;
	}
	return ((int)(num * sign));
}
