/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_struc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabid <mabid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:11:44 by benmoham          #+#    #+#             */
/*   Updated: 2022/06/25 15:25:23 by mabid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * @brief Va attribuer chaque argv a chaque variable
 * 
 * @param info 
 * @param av 
 * @return t_utils_arg* 
 */
t_utils_arg	*init_struc(t_utils_arg *info, char **av)
{
	info->nb_philo = ft_atol(av[1]); // argv [1] pour le nombre de philo
	info->time_die = ft_atol(av[2]); // argv [2] pour le temps pour mourir
	info->time_eat = ft_atol(av[3]); // argv [3] pour le temps de manger
	info->time_sleep = ft_atol(av[4]); // argv [4] pour le temps de dormir
	if (av[5])
		info->nb_eat = ft_atol(av[5]);
	else
		info->nb_eat = 0;
	info->start_time = 0;
	info->finish_eat = 0;
	info->stop = 0;
	return (info);
}

t_utils_philo	*file_struc(t_utils_philo *philo, t_utils_arg *info, char **av)
{
	pthread_t	*thread;
	int			i;
	int			nb;

	i = -1;
	nb = ft_atol(av[1]); //garde dans la variable nb le nombre de philo
	thread = malloc(sizeof(pthread_t) * nb); // Va mallocer les thread par le nombre de philo
	while (++i < nb)
	{
		philo[i].info = init_struc(info, av); // on va attribuer a la variable info a init_struc, info est aussi une structure
		philo[i].thread = thread[i]; // Je donne a ma variable thread (qui est dans une structure) la valeur prise par malloc
		philo[i].id = i + 1;
		philo[i].last_meal = 0;
		philo[i].to_eat = 0;
		pthread_mutex_init(&philo[i].left_fork, NULL); // Declarer un mutex
		if (i == nb - 1)
			philo[i].right_fork = &philo[0].left_fork;
		else
			philo[i].right_fork = &philo[i + 1].left_fork;
	}
	free(thread);
	return (philo);
}