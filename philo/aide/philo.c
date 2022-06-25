/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:13:49 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/15 19:33:19 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*routine(void *arg)
{
	t_utils_philo	*philo;

	philo = (t_utils_philo *)arg;
	while (check_stop(philo->info) == 0)
		take_fork(philo);
	return (NULL);
}

void	finish_prog(t_utils_philo *philo)
{
	int	j;

	j = 0;
	while (check_stop(philo->info) == 0)
	{
		if (check_dead(&philo[j]) == 0 || check_eat(philo) == 0)
		{
			j = 0;
			while (j < philo->info->nb_philo)
			{
				pthread_join(philo[j].thread, NULL);
				j++;
			}
			j = -1;
			while (++j < philo->info->nb_philo)
				pthread_mutex_destroy(&philo[j].left_fork);
			pthread_mutex_destroy(&philo->info->death_mutex);
			pthread_mutex_destroy(&philo->info->write_mutex);
			pthread_mutex_destroy(&philo->info->eat_mutex);
			pthread_mutex_destroy(&philo->info->stop_mutex);
			return ;
		}
	}
}

void	create_thread(t_utils_philo *philo)
{
	int	j;

	j = 0;
	while (j < philo->info->nb_philo)
	{
		pthread_create(&philo[j].thread, NULL, &routine, &philo[j]);
		usleep(2000);
		j++;
	}
	finish_prog(philo);
}

void	start_philo(t_utils_philo *philo)
{
	philo->info->start_time = actual_time();
	pthread_mutex_init(&philo->info->write_mutex, NULL);
	pthread_mutex_init(&philo->info->death_mutex, NULL);
	pthread_mutex_init(&philo->info->eat_mutex, NULL);
	pthread_mutex_init(&philo->info->stop_mutex, NULL);
	create_thread(philo);
}
