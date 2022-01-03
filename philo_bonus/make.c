/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 21:53:51 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/03 20:16:19 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	process_philo(t_philo *var)
{
	char	semaphore[255];
	int		i;

	i = 0;
	philo_sem(var);
	while (i < var->n_ph)
	{
		var->phil[i].info = var;
		var->phil[i].thread_num = i;
		var->phil[i].countime_to_eat = 0;
		var->phil[i].left = (i + 1) % var->n_ph;
		var->phil[i].right = i;
		var->phil[i].param = 1;
		ft_strncpy("philosopher", semaphore, i);
		sem_unlink(semaphore);
		var->phil[i].mt = sem_open(semaphore, O_CREAT, 0660, 1);
		ft_strncpy("start", semaphore, i);
		sem_unlink(semaphore);
		var->phil[i].mtime_to_eat = sem_open(semaphore, O_CREAT, 0660, 1);
		i++;
	}
	return (0);
}

int	philo_sem(t_philo *var)
{
	sem_unlink("fork");
	sem_unlink("end");
	sem_unlink("stop");
	sem_unlink("times");
	var->fork = sem_open("fork", O_CREAT, 0660, var->n_ph);
	var->end = sem_open("end", O_CREAT, 0660, 0);
	var->msg = sem_open("stop", O_CREAT, 0660, 1);
	var->lock = sem_open("times", O_CREAT, 0660, 0);
	var->phil = (t_var *)malloc(sizeof(*(var->phil)) * var->n_ph);
	if (!var->phil)
		return (-1);
	return (1);
}
