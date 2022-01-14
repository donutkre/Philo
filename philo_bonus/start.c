/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:15:12 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/14 11:24:02 by ktiong           ###   ########.fr       */
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
