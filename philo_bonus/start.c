/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:15:12 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/03 20:16:54 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*pre_start(void *args)
{
	t_var		*var;
	pthread_t	threads;

	var = (t_var *)args;
	var->lastime_to_eat = get_time();
	var->talking = var->lastime_to_eat + var->info->time_to_die;
	if (pthread_create(&threads, 0, check_status, args) != 0)
		return ((void *)1);
	pthread_detach(threads);
	while (42)
		philo_routine(var);
	return (0);
}

/**
   Launch each philo's thread, 
   if everyone ate the required amount of rounds,
   display everyone is full.
**/

int	philo_start_threads(t_philo *var)
{
	pthread_t	threads;
	int			i;

	i = 0;
	if (var->num_eat > 0)
	{
		pthread_create(&threads, 0, philo_full, (void *)var);
		pthread_detach(threads);
	}
	var->start_time = get_time();
	while (i < var->n_ph)
	{
		var->phil[i].philo_time = fork();
		if (var->phil[i].philo_time < 0)
			return (0);
		if (var->phil[i].philo_time == 0)
		{
			pre_start(&var->phil[i]);
			exit (0);
		}
		usleep(100);
		i++;
	}
	return (0);
}
