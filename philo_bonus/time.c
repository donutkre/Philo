/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:16:33 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/03 20:17:03 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	struct timeval	current;

	gettimeofday(&current, 0);
	return ((int)(((current.tv_sec) * 1000) + ((current.tv_usec) / 1000)));
}

void	philo_printf(bool status, char *message, t_var *ph)
{
	sem_wait(ph->info->msg);
	printf("\033[32m%lld ms\t \033[0;37mPhilo [%d] %s\n", get_time() \
	- ph->info->start_time, ph->thread_num + 1, message);
	if (status == 1)
		return ;
	sem_post(ph->info->msg);
}
