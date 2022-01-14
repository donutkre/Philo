/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 21:53:51 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/14 11:24:10 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** CREATING PROCESSES
** in the loop at each iteration we assign "links->p" of our philosopher,
** then incrementing the counter for the "d->philos" array of philosophers and
** spawn processes with fork();
** if fork is not equal to 0, then run the life function;
** process and "killing" it;
*/

void	*pre_start_thread(void *arg)
{
	int		i;
	int		forks;
	t_philo	*ph;

	ph = (t_philo *)arg;
	forks = fork();
	if (forks != 0)
		return (0);
	i = 0;
	while (i < ph->n_ph)
	{
		forks = fork();
		if (forks != 0)
		{
			routine(&ph[i]);
			break ;
		}
		i++;
	}
	return (0);
}

/*
** WAITING FOR DELETE PROCESSES
** wait for child processes to terminate
** if status != 3, then none of the philosophers died, in this case philo is full
** through the kill() call, we send a SIGKILL signal to kill the process to each
** from processes;
** clear the reference structure;
*/

int	philo_start_threads(t_philo *ph)
{
	pthread_t	start;
	pthread_t	done;

	if (pthread_create(&start, 0, &pre_start_thread, ph))
		return (clear_state(ph));
	pthread_join(start, 0);
	if (pthread_create(&done, 0, &philo_full_check, ph))
		return (clear_state(ph));
	philo_full(ph);
	pthread_join(done, 0);
	clear_state(ph);
	kill(0, SIGKILL);
	return (0);
}
