/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 23:30:59 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/03 20:16:34 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
   If philo is odd, set up 3 lunch services per round
   One for odds, one for even and one for the last philo.
**/

void	philo_eat(t_var *ph)
{
	sem_wait(ph->info->fork);
	philo_printf(FALSE, BLUE FORK, ph);
	sem_wait(ph->info->fork);
	philo_printf(FALSE, CYAN RFORK, ph);
	sem_wait(ph->mt);
	sem_wait(ph->mtime_to_eat);
	ph->countime_to_eat = 1;
	ph->lastime_to_eat = get_time();
	ph->talking = ph->lastime_to_eat + ph->info->time_to_die;
	if (ph->param == ph->info->num_eat)
		sem_post(ph->info->lock);
	philo_printf(FALSE, YELLOW EAT, ph);
	ph->param++;
	usleep(ph->info->time_to_eat * 1000);
	ph->countime_to_eat = 0;
	sem_post(ph->mtime_to_eat);
	sem_post(ph->mt);
}

void	philo_routine(t_var *ph)
{
	philo_eat(ph);
	philo_printf(FALSE, GREEN SLEEP, ph);
	sem_post(ph->info->fork);
	sem_post(ph->info->fork);
	usleep(ph->info->time_to_sleep * 1000);
	philo_printf(FALSE, PURPLE THINK, ph);
}
