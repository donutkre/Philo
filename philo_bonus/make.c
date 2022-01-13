/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 21:53:51 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/14 01:00:20 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*pre_start_thread(void *arg)
{
	int		i;
	int		forks;
	t_philo	*ph;

	ph = (t_philo *)arg;
	forks = fork();
	if (forks != 0)
		return (0);
	i = 0;
	while (i < ph->n_ph)
	{
		forks = fork();
		if (forks != 0)
		{
			routine(&ph[i]);
			break ;
		}
		i++;
	}
	return (0);
}
