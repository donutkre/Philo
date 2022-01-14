/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 03:36:23 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/14 01:23:05 by ktiong           ###   ########.fr       */
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
	IMPORTANT: Function to clean up the memory
	Free the address and destroy the mutex of the fork
	Free the address amd destroy the mutex of the speak mutex
	Free the struct itself 
*/

int	clear_state(t_philo *state, int status)
{
	while (status > 0)
	{
		if (status == 1)
			free(state);
		if (status == 2)
			pthread_mutex_destroy(state->mt);
		if (status == 3)
			free(state->m_fork);
		if (status == 4)
		{
			while (state->n_ph--)
				pthread_mutex_destroy(&state->m_fork[state->n_ph]);
		}
		status--;
	}
	return (0);
}

/* 
	Check for the currect arguments 
*/

int	check_info(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (ft_putendl_fd(RED"Error : bad arguments.\n", 2));
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 200)
		return (ft_putendl_fd(RED"Error : Wrong number of philosopher\n", 2));
	if (ft_atoi(argv[2]) < 60)
		return (ft_putendl_fd(RED"Error : Wrong number : time to die\n", 2));
	if (ft_atoi(argv[3]) < 60)
		return (ft_putendl_fd(RED"Error : Wrong number : time to eat\n", 2));
	if (ft_atoi(argv[4]) < 60)
		return (ft_putendl_fd(RED"Error : Wrong number : time to sleep\n", 2));
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
		return (ft_putendl_fd(RED"Error : Wrong number of meals\n", 2));
	return (1);
}

/**
    INITIALIZATION OF PHILOSOPHERS
    assign initial values ​​to the variables of the philosopher's object;
	When ph[i].num_meal = 0 all philos ate required amount of time.
**/

void	init_params(int argc, char *argv[], t_philo *ph)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		ph[i].start_philo = get_time(0);
		ph[i].num_meal = 0;
		ph[i].thread_num = i + 1;
		ph[i].n_ph = ft_atoi(argv[1]);
		ph[i].t_die = ft_atoi(argv[2]);
		ph[i].t_eat = ft_atoi(argv[3]);
		ph[i].t_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			ph[i].num_eat = ft_atoi(argv[5]);
		else
			ph[i].num_eat = -1;
		ph[i].right = ph[i].thread_num - 1;
		ph[i].left = ph[i].thread_num % ph[i].n_ph;
	}
}

int	main(int argc, char *argv[])
{
	t_philo	*philo;
	int		phi;
	int		died;
	int		full;

	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philo)
		return (1);
	if (check_info(argc, argv) < 0)
		return (1);
	init_params(argc, argv, philo);
	if (!philo)
		return (1);
	check_end(philo, &died, &full);
	phi = main_process(philo);
	clear_state(philo, phi);
	if (phi)
		return (1);
	return (0);
}
