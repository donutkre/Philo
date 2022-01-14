/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:16:33 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/14 01:01:08 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	thread_create_detach(pthread_t *thread, void *func, void *arg)
{
	if (pthread_create(thread, NULL, func, arg))
		return (-1);
	pthread_detach(*thread);
	return (1);
}

int	get_time(int i)
{
	struct timeval	current;
	int				current_real_time;

	gettimeofday(&current, 0);
	current_real_time = ((current.tv_sec * 1000 + current.tv_usec / 1000) - i);
	return (current_real_time);
}

void	philo_printf(int status, char *message, t_philo *ph)
{
	sem_wait(ph->mt);
	status = get_time(ph->start);
	printf("\033[32m %d \033[0;37m%d %s\n",
		status, ph->thread_num, message);
	if (!*ph->died)
		sem_post(ph->mt);
}
