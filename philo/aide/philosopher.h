/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabid <mabid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 20:11:31 by benmoham          #+#    #+#             */
/*   Updated: 2022/06/25 18:06:35 by mabid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>

# define FORK		"has taken a fork\n"
# define EAT	"is eating\n"
# define SLEEP	  "is sleeping\n"
# define THINK	  "is thinking\n"
# define DEAD		"is dead\n"

typedef struct s_utils_arg
{
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		eat_mutex;
	pthread_mutex_t		stop_mutex;
	long int			time_die;
	long int			time_eat;
	long int			time_sleep;
	long int			start_time;
	int					nb_philo;
	int					nb_eat;
	int					finish_eat;
	int					stop;
}	t_utils_arg;

typedef struct s_utils_philo
{
	struct s_utils_arg	*info;

	pthread_mutex_t		left_fork;
	pthread_mutex_t		*right_fork;
	pthread_t			thread;
	int					id;
	int					to_eat;
	long int			last_meal;
}	t_utils_philo;

long int		actual_time(void);
long int		ft_atol(char *str);
int				check_dead(t_utils_philo *philo);
int				check_stop(t_utils_arg *info);
int				ft_strlen(char *str);
int				check_arg(char **argv);
int				check_max(char *argv);
int				check_eat(t_utils_philo *philo);
int				ft_isdigit(char s);
void			finish_prog(t_utils_philo *philo);
void			take_right_fork(int nb, t_utils_philo *philo);
void			take_fork(t_utils_philo *philo);
void			ft_usleep(long int time_in_ms, t_utils_arg *info);
void			start_philo(t_utils_philo *philo);
void			display_msg(t_utils_philo *philo, char *msg, int check_die);
void			for_eat(t_utils_philo *philo);
void			*routine(void *argv);
t_utils_arg		*init_struc(t_utils_arg *th, char **argv);
t_utils_philo	*file_struc(t_utils_philo *philo, t_utils_arg *info, char **argv);

#endif
