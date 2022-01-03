/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 00:33:46 by ktiong            #+#    #+#             */
/*   Updated: 2021/09/28 00:33:46 by ktiong           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <pthread.h>
# include <stddef.h>

# define GREEN "\033[32m"
# define RED "\e[91m"
# define BLUE "\033[0;34m"
# define YELLOW "\033[0;33m"
# define CYAN "\033[0;36m"
# define PURPLE "\033[0;35m"
# define WHITE "\033[0;37m"
# define MAG   "\x1B[35m"

# define TRUE 1
# define FALSE 0
# define DONE "All philosopher is full"
# define DEAD "is dead"
# define FORK "is picking up left fork"
# define RFORK "is picking up right fork"
# define EAT "is philo_eat"
# define SLEEP "is sleeping"
# define THINK "is thinking"

/*

** n_ph : number of philosophers.
** t_die : time it takes for a philosopher to die.
** t_eat : time it takes for a philosopher to eat.
** t_sleep : time it takes for a philosopher to sleep.
** num_eat : minimum number of time a philosopher must eat.
*/

typedef struct s_var
{
	int					thread_num;
	int					num_meal;
	int					left;
	int					right;
	int					start;
	pthread_t			tid;
	pthread_mutex_t		mt;
	struct s_philo		*state;

}	t_var;

/*
	--Philosophers linked list--

*/

typedef struct s_philo
{
	int					all;
	int					time;
	int					full;
	pthread_mutex_t		*m_fork;
	pthread_mutex_t		m_speak;
	struct s_var		*phil;
	int					n_ph;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					num_eat;

}						t_philo;

int						ft_atoi(const char *thread_num);
int						philo_start_threads(void *arg);
void					philo_eat(t_var *philo);
void					sleeping(t_var *philo);
int						get_time(void);
void					philo_printf(bool status, char *input, t_var *philo);
int						philo_full(t_var *philo);
void					*check_status(void *var);
int						process_philo(t_philo *var);
#endif
