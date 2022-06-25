/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lets_do_it.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:21:28 by mdouiri           #+#    #+#             */
/*   Updated: 2022/06/12 16:25:00 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

u_int64_t	get_time(void)
{
	struct timeval	rent_time;

	gettimeofday(&rent_time, NULL);
	return ((rent_time.tv_sec * 1000) + (rent_time.tv_usec / 1000));
}

void	ft_usleep(t_philo *philo, u_int64_t time)
{
	u_int64_t	start;

	start = get_time();
	while (get_time() - start < time)
	{
		pthread_mutex_lock(&philo->data->death);
		if (philo->data->corpse == 1)
		{
			pthread_mutex_unlock(&philo->data->death);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death);
		usleep(100);
	}
}

int	ft_tea_time(t_philo *philo, int tmp)
{
	pthread_mutex_lock(&philo->data->msg);
	philo->data->current_time = get_time() - philo->data->start_time;
	if (tmp == 1)
	{
		philo->ayd = philo->data->current_time - philo->ls;
		if (philo->status == 0 && philo->ayd > philo->data->time_to_die)
			return (pthread_mutex_unlock(&philo->data->msg), 1);
	}
	else if (tmp == 2)
		philo->ls = philo->data->current_time;
	pthread_mutex_unlock(&philo->data->msg);
	return (0);
}

void	ft_msg(t_philo *philo, int tmp)
{
	static int	die;

	pthread_mutex_lock(&philo->data->msg);
	if (!die)
	{
		philo->status = 0;
		if (tmp == DEAD)
			die = 1;
		if (tmp == EATING)
		{
			philo->meals++;
			philo->status = 1;
		}
		display(philo->data->current_time, philo->id, tmp);
	}
	pthread_mutex_unlock(&philo->data->msg);
}
