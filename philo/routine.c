/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 09:52:15 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/14 01:31:44 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/* 
	Attempt lock function here.
	the last philosopher (with id equal to the given number of philosophers),
	raises the right fork first, while the rest of the philosophers raise
	Only one philo can run the process in lock
	Philo will take his 2 forks if available and start philo_eat.
	Output a message for each fork taken and when he starts to eat.
	Pauses the thread for 1000 ms.
	Count and update the last time Philosopher ate.
	blocking the eating process with the table_manager mutex,
	so that only one philosopher has access to the process;
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
	Take their right fork, no one will be able to eat,
	and they will all die.
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
** THE LIFE CYCLE OF A PHILOSOPHER
** in deadly_counter we initiate the counting of time before the loop
** and reset the counter in the loop every time after eating,
** then check the value of the counter in the death_check function;
** in each iteration we compare the variables eat_counter and time_must_eat,
** if they are equal, then we interrupt the cycle - the philosopher ate a given number of times;
** after the loop is completed, increment the stop_eating counter in
** each thread (philosopher), after which we compare with the number of philosophers,
** if the values ​​are equal, then all philosophers ate a given number of times,
** print "stop eting" and end the program;
**	// link->p->limit = link->p->deadly_timestamp  + link->d->time_to_die;
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
