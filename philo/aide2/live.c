/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:21:44 by mdouiri           #+#    #+#             */
/*   Updated: 2022/06/12 16:21:49 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	ft_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->my_forki);
	ft_msg(philo, FORK);
	pthread_mutex_lock(philo->other_forki);
	ft_msg(philo, FORK);
}

void	ft_eat(t_philo *philo)
{
	ft_tea_time(philo, 2);
	ft_msg(philo, EATING);
	ft_usleep(philo, philo->data->time_to_eat);
}

void	ft_free_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->other_forki);
	pthread_mutex_unlock(&philo->my_forki);
}

void	sleep_now(t_philo *philo)
{
	ft_tea_time(philo, 0);
	ft_msg(philo, SLEEPING);
	ft_usleep(philo, philo->data->time_to_sleep);
}
