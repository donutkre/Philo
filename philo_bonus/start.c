/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:15:12 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/14 09:48:08 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_full_check(void *arg)
{
	t_philo	*ph;
	int		i;

	ph = (t_philo *)arg;
	i = 0;
	while (i++ < ph->n_ph)
		sem_wait(ph->full);
	sem_post(ph->death);
	return (0);
}

void	philo_full(t_philo *ph)
{
	int	i;

	i = 0;
	sem_wait(ph->death);
	while (i < ph->n_ph)
	{
		sem_post(ph->full);
		i++;
	}
}

/*
	CLEANING FUNCTION
	closing semaphores
	clearing allocated memory
*/

int	clear_state(t_philo *ph)
{
	sem_close(ph->m_fork);
	sem_close(ph->mt);
	sem_close(ph->full);
	sem_close(ph->death);
	sem_unlink("m_fork");
	sem_unlink("mt");
	sem_unlink("finished");
	sem_unlink("dead");
	free(ph);
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

sem_t	*ft_sem_open(char *name, int num)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0660, num));
}

/*
	INITIALIZATION OF PHILOSOPHERS
	assign initial values ​​to the variables of the philosopher's object;
	create NAMED semaphores with the sem_open() function (using the same
	function can access already existing named semaphore),
	semaphore m_fork we give the initial value equal to the number of philosophers;
	The write semaphore controls access to the philosopher's status output;
	The dead semaphore controls access to the death check;
*/

int	philo_sem(t_philo *ph)
{
	int		i;
	t_philo	p;

	i = -1;
	p.sem_fork = ft_sem_open("m_fork", ph->n_ph);
	p.sem_message = ft_sem_open("write", 1);
	p.sem_full = ft_sem_open("finished", 0);
	p.sem_dead = ft_sem_open("dead", 0);
	while (++i < ph->n_ph)
	{
		ph[i].start = get_time(0);
		ph[i].num_meal = 0;
		ph[i].full = p.sem_full;
		ph[i].death = p.sem_dead;
		ph[i].mt = p.sem_message;
		ph[i].m_fork = p.sem_fork;
	}
	return (philo_start_threads(ph));
}
