/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 09:52:15 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/14 12:09:58 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
	Attempt lock function here.
	raises the right fork first, while the rest of the philosophers raise
	Only one philo can run the process in lock
	Philo will take his 2 forks if available and start philo_think.
	Output a message for each fork taken and when he starts to eat.
 */

void	take_fork(t_philo *ph)
{
	pthread_mutex_lock(&ph->m_fork[ph->right]);
	philo_printf(0, CYAN FORK, ph);
	pthread_mutex_lock(&ph->m_fork[ph->left]);
	philo_printf(0, BLUE FORK, ph);
}

int	philo_think(t_philo *ph)
{
	philo_printf(0, PURPLE THINK, ph);
	take_fork(ph);
	if (*ph->died)
		return (ERR_DEAD);
	return (0);
}

/*
	If there is no max round declared,
	the while loop will be in infinite loop (eat, sleep, think)
	reset the time of the last meal (get_time());
	print the current status of the philosopher;
	put both forks on the table - first the right one, then the left one,
	so that other philosophers immediately have access to the right fork;
	the philosopher sleeps for a given amount of time (usleep);
*/

int	philo_sleep(t_philo *ph)
{
	int	time;

	philo_printf(0, GREEN SLEEP, ph);
	pthread_mutex_unlock(&ph->m_fork[ph->right]);
	pthread_mutex_unlock(&ph->m_fork[ph->left]);
	if (!ph->num_eat)
		return (0);
	time = get_time(ph->start_philo);
	while (get_time(ph->start_philo) - time < ph->t_sleep)
	{	
		if (*ph->died)
			return (ERR_DEAD);
		usleep(ph->n_ph * 2);
	}
	return (0);
}

/*
	print philo eat status
	Count and update the last time Philosopher ate.
	so that only one philosopher has access to the process;

	in each iteration we compare the variables t_eat and num_meal,
	if they are equal, then we interrupt the cycle - the philosopher
	ate a given number of times;
*/

int	philo_eat(t_philo *ph)
{
	ph->num_meal = get_time(ph->start_philo);
	philo_printf(0, YELLOW EAT, ph);
	while (get_time(ph->start_philo) - ph->num_meal < ph->t_eat)
	{
		if (*ph->died)
			return (ERR_DEAD);
		usleep(ph->n_ph * 2);
	}
	philo_sleep(ph);
	return (0);
}

/*
	Runs through the philo routine.
	After the loop is completed, increment the ph->full counter in
	each thread (philo), after which we compare with the number of philo,
	if the values ​​are equal, then all philo ate a given number of times,
	and reset the counter in the loop every time after eating,
*/

void	*routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (ph->num_eat)
	{
		if (ph->num_eat > 0)
			ph->num_eat--;
		if (philo_think(ph))
			return (0);
		if (philo_eat(ph))
			return (0);
	}
	(*ph->full)++;
	return (0);
}
