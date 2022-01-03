/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 16:55:15 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/03 20:18:15 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
	This function creates a mutex for every fork and assigns 2 forks
	to every philosopher.
	When data->full = 0 all philos ate required amount of time.
**/

int	process_philo(t_philo *var)
{
	int	i;

	var->phil = malloc(sizeof(t_var) * var->n_ph);
	var->m_fork = malloc(sizeof(pthread_mutex_t) * var->n_ph);
	if (!var->phil || !var->m_fork || (pthread_mutex_init(&(var->m_speak), 0)))
		return (-1);
	i = 0;
	while (i < var->n_ph)
	{
		if (pthread_mutex_init(&(var->m_fork[i]), 0))
			return (-1);
		if (pthread_mutex_init(&(var->phil[i].mt), 0))
			return (-1);
		var->phil[i].state = var;
		var->phil[i].thread_num = i;
		var->phil[i].num_meal = 0;
		var->phil[i].left = i;
		var->phil[i].right = (i + 1) % var->n_ph;
		i++;
	}
	return (0);
}
