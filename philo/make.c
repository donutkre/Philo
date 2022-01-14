/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 16:55:15 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/14 09:34:35 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
	This function creates a mutex for every fork and assigns 2 forks
	to every philosopher.
    allocate memory for an array of forks (mutex);
    initialize mutex forks (pthread_mutex_init) according to
    the number of philosophers
	assign initial values ​​to the variables of the philosopher's object;
	write mutex initialization (controls access to status output);
	initialization of the death mutex (controls access to the death check);
	call the function that initializes the forks;
	call the function that initializes the philosophers;
**/

int	process_philo(t_philo *ph, pthread_mutex_t m_speak)
{
	int				i;
	pthread_mutex_t	*m_fork;

	m_fork = malloc(sizeof(pthread_mutex_t) * ph->n_ph);
	if (!m_fork)
		return (ERR_MALLOC);
	i = 0;
	while (i < ph->n_ph)
	{
		if (pthread_mutex_init(&m_fork[i], 0))
		{
			while (i--)
				pthread_mutex_destroy(&m_fork[i]);
			return (ERR_MUTEX);
		}
		i++;
	}
	while (i--)
	{
		ph[i].mt = &m_speak;
		ph[i].m_fork = m_fork;
	}
	return (philo_start_threads(ph));
}

/**
	write mutex initialization (controls access to status output);
	and call for process_philo

	assign initial values ​​to the variables of the philosopher's object;
	write mutex initialization (controls access to status output);
	initialization of the death mutex (controls access to the death check);
	call the function that initializes the forks;
	call the function that initializes the philosophers;
	allocate memory for the threads array;
**/

int	main_process(t_philo *ph)
{
	pthread_mutex_t	write;

	if (pthread_mutex_init(&write, 0))
		return (0);
	return (process_philo(ph, write));
}

void	check_end(t_philo *ph, int *died, int *full)
{
	int	i;

	i = 0;
	*died = 0;
	*full = 0;
	while (i < ph->n_ph)
	{
		ph[i].died = died;
		ph[i].full = full;
		i++;
	}
}
