/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 03:49:21 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/14 09:29:04 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(int i)
{
	struct timeval	current;
	int				current_real_time;

	gettimeofday(&current, 0);
	current_real_time = (current.tv_sec * 1000 + current.tv_usec / 1000);
	current_real_time -= i;
	return (current_real_time);
}

/*
	Displays timestamp log status in console log.
	Also checks if a philo is dead or full.
	Attempt lock and unlock function here
*/

void	philo_printf(int status, char *message, t_philo *ph)
{
	pthread_mutex_lock(ph->mt);
	if (*ph->died)
	{
		pthread_mutex_unlock(ph->mt);
		return ;
	}
	status = get_time(ph->start_philo);
	printf("\033[32m%d\033[0;37m %d %s\n",
		status, ph->thread_num, message);
	pthread_mutex_unlock(ph->mt);
}
