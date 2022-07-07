/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabid <mabid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:29:35 by mabid             #+#    #+#             */
/*   Updated: 2022/07/07 13:29:41 by mabid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_dead(t_utils_philo *philo)
{
	pthread_mutex_lock(&philo->info->death_mutex);
	if ((actual_time() - philo->info->start_time)
		- philo->last_meal >= philo->info->time_die) // Si le temps restant - le start time et - le repqs est supérieur ou egal a time to die, alors on demarre le process
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

/**
 * @brief Va verifier les mutex
 * 
 * @param info 
 * @return int 
 */
int	check_stop(t_utils_arg *info)
{
	int	ret;

	pthread_mutex_lock(&info->stop_mutex); //Va fermer le mutex pendant un temps x le temps que le philo mange
	ret = info->stop;
	pthread_mutex_unlock(&info->stop_mutex); // une fois qu'il a fini il libere le mutex
	return (ret);
}

/**
 * @brief Uniquement pour verifier si le nombre de repas limiter est atteint
 * 
 * @param philo 
 * @return int 
 */
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
