/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:22:03 by mdouiri           #+#    #+#             */
/*   Updated: 2022/06/12 16:43:18 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	mini_main(t_general **data, t_philo **philo, int ac, char **av)
{
	if (init_data(data, av, ac) != 0)
		return (0);
	if (init_philo(philo, *data) != 0)
		return (free(*data), 0);
	(*data)->phila = *philo;
	if ((*data)->nb_philo == 1)
		return (one_philo(*philo), free(*data), free(*philo), 0);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_general	*d;
	t_philo		*philo;

	philo = NULL;
	d = NULL;
	if ((ac < 5 || ac > 7) || !env)
		return (write(1, "Error\n", 6), 0);
	if (!mini_main(&d, &philo, ac, av))
		return (0);
	d->start_time = get_time();
	while (++(d->i) < d->nb_philo)
	{
		if (pthread_create(&(philo[d->i].who), NULL, &orga, &(philo[d->i])))
			return (write(1, "error pthread_create\n", 21), 0);
	}
	if (pthread_create(&(d->control), NULL, &police, (d)))
		return (write(1, "error pthread_create\n", 21), 0);
	while (++(d->v) < d->nb_philo)
	{
		if (pthread_join(philo[d->v].who, NULL))
			return (write(1, "error pthread_join\n", 19), 0);
	}
	if (pthread_join(d->control, NULL))
		return (write(1, "error pthread_join\n", 19), 0);
	return (free(d), free(philo), 0);
}
