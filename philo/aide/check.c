/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:34:18 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/14 16:34:51 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_dead(t_utils_philo *philo)
{
	pthread_mutex_lock(&philo->info->death_mutex);
	if ((actual_time() - philo->info->start_time)
		- philo->last_meal >= philo->info->time_die)
	{
		display_msg(philo, DEAD, 1);
		pthread_mutex_lock(&philo->info->stop_mutex);
		philo->info->stop = 1;
		pthread_mutex_unlock(&philo->info->stop_mutex);
		pthread_mutex_unlock(&philo->info->death_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->info->death_mutex);
	return (1);
}

int	check_stop(t_utils_arg *info)
{
	int	ret;

	pthread_mutex_lock(&info->stop_mutex);
	ret = info->stop;
	pthread_mutex_unlock(&info->stop_mutex);
	return (ret);
}

int	check_eat(t_utils_philo *philo)
{
	pthread_mutex_lock(&philo->info->eat_mutex);
	if (philo->info->finish_eat == philo->info->nb_eat
		&& philo->info->nb_eat != 0)
	{
		pthread_mutex_lock(&philo->info->stop_mutex);
		philo->info->stop = 1;
		pthread_mutex_unlock(&philo->info->stop_mutex);
		pthread_mutex_unlock(&philo->info->eat_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->info->eat_mutex);
	return (1);
}
