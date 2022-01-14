/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 03:38:39 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/14 11:25:41 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Prints death message
*/

void	death_message(int s, int philo, char *message, t_philo *ph)
{
	s = get_time(ph->start_philo);
	printf("\033[32m%d\033[0;37m %d %s\n",
		s, philo, message);
	pthread_mutex_unlock(ph->mt);
}

/*
	This function checks if philo will die during
	next round and inform next death time.
	The simulation stops as soon as one philo dies.
	Checks if any Philo die, return death message.
	Check for death in a side-by-side thread.
	Also checks if philo ate enough times. if yes, exit.
	get_time(ph->start_philo) - ph[i].num_meal
	from the current time we subtract the timestamp at the moment of the last
	eating thus getting the amount of time that the philosopher
	remained without food and then compare with the input parameter of the valid
    if the elapsed time without food is more than indicated
*/

void	check_status(t_philo *ph)
{
	int	i;

	i = 0;
	while (ERR_DEAD)
	{
		if (get_time(ph->start_philo) - ph[i].num_meal > ph[i].t_die
			&& ph[i].num_eat)
		{
			death_message(0, ph[i].thread_num, RED DEAD, ph);
			*ph->died = 1;
			i = 0;
			while (i < ph->n_ph)
				pthread_mutex_unlock(&ph->m_fork[i++]);
			break ;
		}
		if (*ph->full == ph->n_ph)
			break ;
		i++;
		if (i == ph->n_ph)
		{
			i = 0;
			usleep(500);
		}
	}
}

/*** 
	allocate memory for the threads array
  	declare an array of structures-references to structures, allocate memory
	in the loop, we assign values ​​to each of the reference structures
	in the same place we create threads (pthread_create) with access to
	the routine function
	we wait for the completion of threads using the pthread_join function
	Create the philo here
	philo_start_threads will launch each philo's thread and join em.
	Checks if philo has died or has eaten enough time, if yes, display output.
*/

int	philo_start_threads(t_philo *var)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * var->n_ph);
	if (!threads)
		return (ERR_THREAD);
	while (i < var->n_ph)
	{
		if (pthread_create(&threads[i], 0, &routine, &var[i]))
		{
			while (i--)
				pthread_join(threads[i], 0);
			free(threads);
			return (ERR_THREAD);
		}
		usleep(100);
		i++;
	}
	check_status(var);
	usleep(1000);
	while (i--)
		pthread_join(threads[i], 0);
	free(threads);
	return (clear_state(var, ERR_THREAD));
}
