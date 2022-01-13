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

# include <stdbool.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# define GREEN "\033[32m"
# define RED "\e[91m"
# define BLUE "\033[0;34m"
# define YELLOW "\033[0;33m"
# define CYAN "\033[0;36m"
# define PURPLE "\033[0;35m"
# define WHITE "\033[0;37m"
# define MAG   "\x1B[35m"
# define ERR                    1
# define ERR_MALLOC     2
# define ERR_MUTEX              3
# define ERR_THREAD     4
# define ERR_DEAD     -2
# define TRUE 1
# define FALSE 0
# define DONE "All philosopher is full"
# define DEAD "died"
# define FORK "has taken a fork"
# define RFORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

typedef struct s_var
{
	int				thread_num;
	int				num_meal;
	struct t_philo	*philo;
	struct s_philo	*state;

}				t_var;

typedef struct s_philo
{
	int				n_ph;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				num_eat;
	int				num_meal;
	int				thread_num;
	int				right;
	int				left;
	int				start_philo;
	int				*died;
	int				*full;
	pthread_mutex_t	*mt;
	pthread_mutex_t	*m_fork;
}				t_philo;

int			ft_atoi(const char *c);
int			philo_start_threads(t_philo *var);
void		*routine(void *arg);
int			ft_putendl_fd(char *s, int fd);
int			get_time(int i);
void		philo_printf(int status, char *message, t_philo *ph);
int			clear_state(t_philo *state, int status);
void		check_end(t_philo *ph, int *died, int *full);
int			main_process(t_philo *ph);

#endif
