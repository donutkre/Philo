/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:14:57 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/03 20:15:31 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
   Semaphore:
   When a philo (thread) start, semaphore value decrease.
**/

#include "philo.h"

void	*philo_full(void *args)
{
	t_philo	*ph;
	int		i;

	ph = (t_philo *)args;
	i = -1;
	while (++i < ph->n_ph)
		sem_wait(ph->lock);
	philo_printf(TRUE, GREEN DONE, ph->phil);
	sem_post(ph->phil->mt);
	sem_post(ph->end);
	return (0);
}

/**
   if someone dies, display console message
**/

void	*check_status(void	*args)
{
	t_var		*ph;
	int64_t		time;

	ph = (t_var *)args;
	while (42)
	{
		sem_wait(ph->mt);
		time = get_time();
		if (!ph->countime_to_eat && time > ph->talking)
		{
			philo_printf(TRUE, RED DEAD, ph);
			sem_post(ph->mt);
			sem_post(ph->info->end);
		}
		sem_post(ph->mt);
		usleep(1000);
	}
}

/**

   When info->full == 0 = ate required amount of time
**/

void	init_params(t_philo *info, int argc, char *argv[])
{
	info->n_ph = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc < 5 || argc > 6)
		printf("%d Incorrect arguments, please input 5 or 6.\n", (argc - 1));
	if (argv[5])
		info->num_eat = ft_atoi(argv[5]);
	else
		info->num_eat = 0;
	if ((info->n_ph < 2 || info->n_ph > 200 || info->time_to_die < 60
			|| info->time_to_eat < 60 || info->time_to_sleep < 60
			|| info->num_eat < 0))
	info->full = 0;
	info->forks = "fork";
	info->death = "done";
	info->datas = "msg";
	info->counts = "info";
}

/**
   Check error/argc parsing and start threads.
**/
int	main(int argc, char *argv[])
{
	t_philo	*var;

	if (argc < 5 || argc > 6)
	{
		printf("%d Incorrect arguments, please input 5 or 6.\n", (argc - 1));
		return (0);
	}
	var = malloc(sizeof(t_philo));
	if (!var)
		return (0);
	init_params(var, argc, argv);
	process_philo(var);
	philo_start_threads(var);
	sem_wait(var->end);
	return (0);
}
