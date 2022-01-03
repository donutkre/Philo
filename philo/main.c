/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 03:36:23 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/03 20:14:46 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	The objective of this project is to make the philosopher stay alive.
	Each philosopher is a thread and each fork is a mutex.
	They program in the following order: Eat, Sleep, Think.
	Each of them must have two forks (think of it as chopstick).
	Left fork belongs to the philosopher and borrows right fork 
	from philosopher beside them.
	If one philosopher dies, the simulation will stop and display 
	death in console log.
*/

/*
	If philo ate enough times. exit without sleep status.
	Output done philo_eat message once each philo ate the required amount of times.
*/

int	philo_full(t_var *ph)
{
	if (ph->num_meal == ph->state->num_eat)
		ph->state->all++;
	if (ph->state->all == ph->state->n_ph)
	{
		philo_printf(TRUE, GREEN DONE, ph);
		return (-1);
	}
	return (1);
}

/*
	This function checks if philo will die during,
	next round and inform next death time.
	The simulation stops as soon as one philo dies.
	Checks if any Philo die, return death message.
	Check for death in a side-by-side thread.
*/

void	*check_status(void *var)
{
	t_var	*ph;

	ph = (t_var *)var;
	while (!ph->state->full)
	{
		pthread_mutex_lock(&(ph->mt));
		if (get_time() - ph->start >= ph->state->t_die)
		{
			philo_printf(TRUE, RED DEAD, ph);
			pthread_mutex_unlock(&(ph->mt));
			return (0);
		}
		pthread_mutex_unlock(&(ph->mt));
		usleep(1000);
	}
	return (0);
}

/* 
	IMPORTANT: Function to clean up the memory
	Free the address and destroy the mutex of the fork
	Free the address amd destroy the mutex of the speak mutex
	Free the struct itself 
*/
void	clear_state(t_philo *state)
{
	int	i;

	usleep(1000);
	i = -1;
	pthread_mutex_destroy(&state->m_speak);
	while (++i < state->n_ph)
		pthread_mutex_destroy(&state->m_fork[i]);
	free(state->phil);
	free(state->m_fork);
}

/* 
	Check for the currect arguments 
*/

int	init_params(t_philo *var, int argc, char *argv[])
{
	var->n_ph = ft_atoi(argv[1]);
	var->t_die = ft_atoi(argv[2]);
	var->t_eat = ft_atoi(argv[3]);
	var->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		var->num_eat = ft_atoi(argv[5]);
	if ((var->n_ph < 0 || var->n_ph >= 200 || var->t_die < 60
			|| var->t_eat < 60 || var->t_sleep < 60)
		|| (argc == 6 && var->num_eat < 0))
		return (0);
	return (1);
}

/*
	Main program will check error parsing then start threads
*/

int	main(int argc, char *argv[])
{
	t_philo	var;

	memset(&var, 0, sizeof(t_philo));
	if (argc < 5 || argc > 6)
		return (printf("\e[91mIncorrect arguments, please input 5 or 6.\n"));
	if (init_params(&var, argc, argv) == 0)
	{
		printf("\e[91mIncorrect argc\n");
		return (1);
	}
	if (process_philo(&var) < 0)
		return (printf("\e[91mMalloc error\n"));
	philo_start_threads(&var);
	clear_state(&var);
	return (0);
}
