/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:04:04 by mdouiri           #+#    #+#             */
/*   Updated: 2022/06/10 18:15:43 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdarg.h>

struct	s_philo;

typedef struct s_general
{
	u_int64_t		start_time;
	u_int64_t		time_to_die;
	u_int64_t		time_to_sleep;
	u_int64_t		time_to_eat;
	u_int64_t		current_time;
	int				max_meals;
	int				nb_philo;
	int				corpse;
	int				sated;
	int				i;
	int				v;
	pthread_mutex_t	msg;
	pthread_mutex_t	sleep_msg;
	pthread_mutex_t	eat;
	pthread_mutex_t	think;
	pthread_mutex_t	tea_time;
	pthread_mutex_t	death;
	pthread_mutex_t	timo;
	pthread_mutex_t	ft_forki;
	pthread_t		control;
	struct s_philo	*phila;
}	t_general;

typedef struct s_philo
{
	u_int64_t		ayd;
	u_int64_t		ls;
	pthread_t		who;
	pthread_mutex_t	my_forki;
	pthread_mutex_t	*other_forki;
	int				id;
	int				status;
	int				thinking;
	int				ok;
	int				available_forki;
	int				meals;
	t_general		*data;
}	t_philo;

enum e_states
{
	THINKING,
	EATING,
	FORK,
	DEAD,
	SLEEPING,
};
void		*orga(void *phila);
void		think_my_friend(t_philo *philo);
void		sleep_now(t_philo *philo);
void		eat_my_philo_eat(t_philo *philo);
void		ft_fork(t_philo *philo);
void		ft_eat(t_philo *philo);
void		ft_free_fork(t_philo *philo);
void		ft_msg(t_philo *philo, int tmp);
void		*police(void *philu);
void		display(long long time, int id, int states);
void		ft_putnbr_u(u_int64_t nb);
void		ft_tri(t_philo *philo);
void		ft_usleep(t_philo *philo, u_int64_t time);
void		one_philo(t_philo *philo);
char		*whatsup(int tmp);
int			ft_tea_time(t_philo *philo, int tmp);
int			ft_atoi(char *str);
int			init_data(t_general **dato, char **av, int ac);
int			init_philo(t_philo **phila, t_general *data);
int			fbi(t_general *data);
int			mini_main(t_general **data, t_philo **philo, int ac, char **av);
u_int64_t	get_time(void);

#endif
