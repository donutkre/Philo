/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiong <ktiong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 04:56:36 by ktiong            #+#    #+#             */
/*   Updated: 2022/01/03 20:06:36 by ktiong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <stdbool.h>

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
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

typedef struct s_var
{
	intmax_t			talking;
	struct s_philo		*info;
	int					thread_num;
	int					countime_to_eat;
	int					left;
	int					right;
	pid_t				philo_time;
	int					param;
	intmax_t			lastime_to_eat;
	sem_t				*mt;
	sem_t				*mtime_to_eat;
}			t_var;

typedef struct s_philo
{
	int				n_ph;
	intmax_t		time_to_die;
	intmax_t		time_to_eat;
	intmax_t		time_to_sleep;
	int				num_eat;
	t_var			*phil;
	sem_t			*fork;
	sem_t			*msg;
	int				full;
	int64_t			start_time;
	char			*datas;
	char			*death;
	char			*forks;
	char			*counts;
	sem_t			*end;
	sem_t			*lock;
}				t_philo;

char		*ft_strncpy(char *src, char *dst, int n);
int			ft_atoi(const char *nbr);
int			philo_start_threads(t_philo *var);
int			get_time(void);
void		philo_printf(bool status, char *message, t_var *ph);
int			process_philo(t_philo *var);
char		*ft_strncpy(char *src, char *dst, int n);
void		*pre_start(void *args);
void		*check_status(void *args);
void		philo_routine(t_var *philo);
void		*philo_full(void *args);
int			philo_sem(t_philo *var);
#endif
