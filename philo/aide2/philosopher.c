/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:22:17 by mdouiri           #+#    #+#             */
/*   Updated: 2022/06/12 16:22:21 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	one_philo(t_philo *philo)
{
	ft_msg(philo, FORK);
	display(philo->data->time_to_die + 1, philo->id, DEAD);
}

void	conditions(t_philo *philo, int tmp)
{
	if (tmp == 1)
	{
		if (philo->id % 2)
		{
			if (philo->id == philo->data->nb_philo)
				ft_usleep(philo, philo->data->time_to_eat);
			ft_usleep(philo, 30);
		}
	}
	else if (tmp == 2)
	{
		pthread_mutex_lock(&philo->data->eat);
		if (philo->data->max_meals != -1 && philo->ok == 0
			&& philo->meals >= philo->data->max_meals)
		{
			philo->data->sated++;
			philo->ok = 1;
		}
		pthread_mutex_unlock(&philo->data->eat);
	}
}

void	*orga(void *phila)
{
	t_philo	*philo;

	philo = (t_philo *)phila;
	conditions(philo, 1);
	while (1)
	{
		ft_fork(philo);
		ft_eat(philo);
		ft_free_fork(philo);
		conditions(philo, 2);
		sleep_now(philo);
		pthread_mutex_lock(&philo->data->death);
		if (philo->data->corpse)
			return (pthread_mutex_unlock(&philo->data->death), NULL);
		pthread_mutex_unlock(&philo->data->death);
		ft_msg(philo, THINKING);
	}
	return (NULL);
}

int	fbi(t_general *data)
{
	pthread_mutex_lock(&data->eat);
	if (data->max_meals != -1 && data->sated == data->nb_philo)
	{
		pthread_mutex_lock(&data->death);
		data->corpse = 1;
		pthread_mutex_unlock(&data->death);
		pthread_mutex_unlock(&data->eat);
		return (1);
	}
	pthread_mutex_unlock(&data->eat);
	return (0);
}

void	*police(void *philu)
{
	t_general	*data;
	int			i;

	data = (t_general *)philu;
	while (!data->corpse)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			if (ft_tea_time(&data->phila[i], 1) == 1)
			{
				pthread_mutex_lock(&data->death);
				data->corpse = 1;
				pthread_mutex_unlock(&data->death);
				ft_msg(&data->phila[i], DEAD);
				return (NULL);
			}
			if (fbi(data) == 1)
				return (NULL);
		}
	}
	return (NULL);
}
