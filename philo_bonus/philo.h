/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 04:56:36 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/14 01:00:37 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <errno.h>
# include <pthread.h>
# include <signal.h>
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
# define SEM_END "/sem_end"
# define SEM_FULL "/sem_full"
# define SEM_FORK "/sem_fork"
# define SEM_PRINT "/sem_print"

typedef struct s_philo {
	int		n_ph;
	int		t_die;
	int		t_sleep;
	int		t_eat;
	int		num_eat;
	int		num_meal;
	int		thread_num;
	int		start;
	int		*died;
	sem_t	*m_fork;
	sem_t	*mt;
	sem_t	*death;
	sem_t	*full;
	sem_t	*sem_fork;
	sem_t	*sem_message;
	sem_t	*sem_dead;
	sem_t	*sem_full;
}				t_philo;

int			ft_atoi(const char *c);
int			get_time(int i);
t_philo		*create_philo(int argc, char **argv, int *died);
void		philo_full(t_philo *ph);
int			philo_sem(t_philo *ph);
void		*pre_start_thread(void *arg);
void		philo_printf(int status, char *message, t_philo *ph);
void		*philo_full_check(void *arg);
int			ft_putendl_fd(char *s, int fd);
int			routine(t_philo *philo);
int			check_info(int argc, char *argv[]);
void		*check_status(void *arg);
int			thread_create_detach(pthread_t *thread, void *func, void *arg);
#endif
