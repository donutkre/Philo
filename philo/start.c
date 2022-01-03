/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 03:38:39 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/03 20:18:47 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*

   	Delay odd philo, even goes first.s
	Checks if total number of philosophers is even or odd.
	Make even or odd philo a delay, if all philo start at the same time,
	and take their right fork, no one will be able to eat,
	and they will all die.
	If there is no max round declared,
	the while loop will be in infinite loop (eat, sleep, think)
*/
void	*start_philo(void *var)
{
	t_var	*ph;
	int		th_num;

	ph = (t_var *)var;
	if (!(ph->thread_num % 2))
		usleep(1000 * ph->state->t_eat);
	while (!ph->state->full)
	{
		philo_eat(ph);
		if (ph->state->num_eat != -1 && philo_full(ph) < 0)
			break ;
		philo_printf(FALSE, GREEN SLEEP, ph);
		th_num = get_time();
		while (!ph->state->full && \
		get_time() - th_num <= ph->state->t_sleep)
			usleep(1000);
		if (ph->state->full)
			break ;
		philo_printf(FALSE, PURPLE THINK, ph);
	}
	return (0);
}

/*
	Create the philo here.
	philo_start_threads will launch each philo's thread and join em.
	Checks if philo has died or has eaten enough time, if yes, display output.
*/

int	philo_start_threads(void *arg)
{
	pthread_t	threads;
	t_philo		*var;
	int			i;

	i = 0;
	var = (t_philo *) arg;
	var->time = get_time();
	while (i < var->n_ph)
	{
		var->phil[i].start = get_time();
		if (pthread_create(&threads, NULL, start_philo, &(var->phil[i])))
			return (EXIT_FAILURE);
		pthread_detach(threads);
		if (pthread_create(&(var->phil[i].tid), \
		NULL, check_status, &(var->phil[i])))
			return (EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < var->n_ph)
	{
		pthread_join(var->phil[i].tid, 0);
		i++;
	}
	return (1);
}
