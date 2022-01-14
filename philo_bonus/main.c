/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:14:57 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/14 12:09:43 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
   Semaphore:
   When a philo (thread) start, semaphore value decrease.
**/

/*
	get_time(ph->start) - ph->num_meal > ph->t_die
	from the current time we subtract the timestamp at the moment of the last
	eating thus getting the amount of time that the philosopher
	remained without food and then compare with the input parameter of the valid
	time to death; if the elapsed time without food is more than indicated
	in the argument, then we end the program
*/

#include "philo.h"

void	*check_status(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (1)
	{
		if (*ph->died)
			break ;
		if (get_time(ph->start) - ph->num_meal > ph->t_die)
		{
			*ph->died = 1;
			philo_printf(get_time(ph->start), RED DEAD, ph);
			sem_post(ph->death);
			break ;
		}
		usleep(500);
	}
	return (0);
}

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

/*
	STORING ARGUMENTS TO VARIABLES AND CALLING INITIALIZING FUNCTIONS
*/

t_philo	*init_params(int argc, char *argv[], t_philo *ph, int *status)
{
	int		i;

	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		ph[i].n_ph = ft_atoi(argv[1]);
		ph[i].t_die = ft_atoi(argv[2]);
		ph[i].t_eat = ft_atoi(argv[3]);
		ph[i].t_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			ph[i].num_eat = ft_atoi(argv[5]);
		else
			ph[i].num_eat = -1;
		ph[i].thread_num = i + 1;
		*status = 0;
		ph[i].died = status;
	}
	return (ph);
}

t_philo	*create_philo(int argc, char *argv[], int *died)
{
	t_philo	*ph;

	ph = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!ph)
		return (0);
	ph = init_params(argc, argv, ph, died);
	return (ph);
}

int	main(int argc, char *argv[])
{
	t_philo		*ph;
	int			full;

	if (check_info(argc, argv) == -1)
		return (0);
	ph = create_philo(argc, argv, &full);
	if (!ph)
		return (0);
	philo_sem(ph);
	free(ph);
}
