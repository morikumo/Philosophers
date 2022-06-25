/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:21:07 by mdouiri           #+#    #+#             */
/*   Updated: 2022/06/12 16:24:23 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	ft_atoi(char *str)
{
	int			i;
	long int	x;

	i = 0;
	x = 0;
	if (!str || !str[0] || str[0] == '-' || str[0] == '+')
		return (-1);
	while (str[i] >= 48 && str[i] <= 57)
	{
		x = (x * 10) + (str[i] - 48);
		i++;
	}
	if (str[i] && (str[i] < 48 || str[i] > 57))
		return (-1);
	if (x > 2147483647 || x < -2147483648)
		return (-1);
	return (x);
}

int	check_all(char **av, int ac)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	init_data(t_general **dato, char **av, int ac)
{
	if (check_all(av, ac) == -1)
		return (-1);
	*dato = (t_general *)malloc(sizeof(**dato));
	if (!*dato)
		return (-1);
	(*dato)->nb_philo = ft_atoi(av[1]);
	(*dato)->time_to_die = ft_atoi(av[2]);
	(*dato)->time_to_eat = ft_atoi(av[3]);
	(*dato)->time_to_sleep = ft_atoi(av[4]);
	(*dato)->corpse = 0;
	(*dato)->sated = 0;
	(*dato)->current_time = 0;
	(*dato)->i = -1;
	(*dato)->v = -1;
	(*dato)->max_meals = ft_atoi(av[5]);
	pthread_mutex_init(&(*dato)->msg, NULL);
	pthread_mutex_init(&(*dato)->sleep_msg, NULL);
	pthread_mutex_init(&(*dato)->death, NULL);
	pthread_mutex_init(&(*dato)->eat, NULL);
	pthread_mutex_init(&(*dato)->ft_forki, NULL);
	(*dato)->phila = NULL;
	return (0);
}

int	init_philo(t_philo **phila, t_general *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	*phila = (t_philo *)malloc(sizeof(**phila) * data->nb_philo);
	if (!*phila)
		return (-1);
	philo = *phila;
	while (++i < data->nb_philo)
	{
		(philo)[i].ls = 0;
		(philo)[i].id = i + 1;
		(philo)[i].available_forki = 0;
		(philo)[i].data = data;
		(philo)[i].thinking = 0;
		(philo)[i].status = 0;
		(philo)[i].meals = 0;
		(philo)[i].ok = 0;
		pthread_mutex_init(&((philo)[i].my_forki), NULL);
		if (i == data->nb_philo -1)
			(philo)[i].other_forki = &((philo)[0].my_forki);
		else
			(philo)[i].other_forki = &((philo)[i + 1].my_forki);
	}
	return (0);
}
