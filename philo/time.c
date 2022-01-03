/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 03:49:21 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/03 20:18:58 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
	Calculated in millisec
	1ms = 1000us (microseconds, usleep) 
*/

int	get_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((int)(((current.tv_sec) * 1000) + ((current.tv_usec) / 1000)));
}

/*
	Displays timestamp log status in console log.
	Also checks if a philo is dead or full.
	Attempt lock and unlock function here
*/

void	philo_printf(bool status, char *message, t_var *ph)
{
	pthread_mutex_lock(&ph->state->m_speak);
	if (ph->state->full)
	{
		pthread_mutex_unlock(&ph->state->m_speak);
		return ;
	}
	printf("\033[32m%d ms\t \033[0;37mPhilo [%d] %s\n", get_time() \
	- ph->state->time, ph->thread_num + 1, message);
	if (status)
	{
		ph->state->full = 1;
	}
	pthread_mutex_unlock(&ph->state->m_speak);
}
