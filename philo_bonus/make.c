/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 21:53:51 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/14 09:47:14 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** CREATING PROCESSES
** in the loop at each iteration we assign "links->p" of our philosopher,
** then incrementing the counter for the "d->philos" array of philosophers and
** spawn processes with fork();
** if fork is not equal to 0, then run the life function;
** process and "killing" it;
*/

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
