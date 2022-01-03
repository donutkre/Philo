/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 09:52:15 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/03 20:18:30 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
	Attempt lock function here.
	Only one philo can run the process in lock
	Philo will take his 2 forks if available and start philo_eat.
	Output a message for each fork taken and when he starts to eat.
	Pauses the thread for 1000 ms.
	Count and update the last time Philosopher ate.
 */

void	philo_eat(t_var *ph)
{
	pthread_mutex_lock(&ph->state->m_fork[ph->left]);
	philo_printf(FALSE, BLUE FORK, ph);
	pthread_mutex_lock(&ph->state->m_fork[ph->right]);
	philo_printf(FALSE, CYAN RFORK, ph);
	pthread_mutex_lock(&(ph->mt));
	philo_printf(FALSE, YELLOW EAT, ph);
	ph->start = get_time();
	pthread_mutex_unlock(&(ph->mt));
	while (!ph->state->full && \
	get_time() - ph->start <= ph->state->t_eat)
		usleep(1000);
	ph->num_meal++;
	pthread_mutex_unlock(&ph->state->m_fork[ph->left]);
	pthread_mutex_unlock(&ph->state->m_fork[ph->right]);
}
