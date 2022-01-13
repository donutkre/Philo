/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 23:30:59 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/14 01:00:49 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *ph)
{
	sem_wait(ph->m_fork);
	philo_printf(get_time(ph->start), CYAN FORK, ph);
	sem_wait(ph->m_fork);
	philo_printf(get_time(ph->start), BLUE FORK, ph);
}

int	philo_think(t_philo *ph)
{
	philo_printf(get_time(ph->start), PURPLE THINK, ph);
	take_fork(ph);
	return (0);
}

void	philo_sleep(t_philo *ph)
{
	philo_printf(get_time(ph->start), GREEN SLEEP, ph);
}

int	philo_eat(t_philo *ph)
{
	int	time;

	ph->num_meal = get_time(ph->start);
	if (*ph->died)
		return (1);
	philo_printf(get_time(ph->start), YELLOW EAT, ph);
	while (get_time(ph->start) - ph->num_meal < ph->t_eat)
		usleep(ph->n_ph * 2);
	sem_post(ph->m_fork);
	sem_post(ph->m_fork);
	if (!ph->num_eat)
		return (0);
	time = get_time(ph->start);
	while (get_time(ph->start) - time < ph->t_sleep)
		usleep(ph->n_ph * 2);
	philo_sleep(ph);
	return (0);
}

int	routine(t_philo *ph)
{
	pthread_t	thread;

	if ((thread_create_detach(&thread, &check_status, ph)) < 0)
		return (-1);
	while (ph->num_eat)
	{
		if (ph->num_eat > 0)
			ph->num_eat--;
		if (philo_think(ph))
			break ;
		if (philo_eat(ph))
			break ;
	}
	*ph->died = 1;
	pthread_join(thread, 0);
	sem_post(ph->full);
	return (0);
}
