/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabid <mabid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:20:06 by benmoham          #+#    #+#             */
/*   Updated: 2022/06/25 15:15:05 by mabid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_usleep(long int time_in_ms, t_utils_arg *info)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	(void)info;
	while ((actual_time() - start_time) < time_in_ms)
	{
		if (check_stop(info) == 1)
			break ;
		usleep(50);
	}
}

long int	actual_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		return (-1);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

int	main(int ac, char **av)
{
	t_utils_philo	*philo;
	t_utils_arg		info;

	if (ac > 6 || ac < 5) // Ba verifier si il y a bien le bon nombre de ac
	{
		printf("wrong argument\n");
		return (1);
	}
	if (check_arg(av) == 1)  // parsing. Verifie si l'argument passer est bien un chiffre et si il est valable
		return (1);
	philo = malloc(sizeof(t_utils_philo) * ft_atol(av[1])); // argv[1 est le nombre de philo on va donc bien preparer la pile en fonction du nombre de philo 
	if (!philo)
		return (-1);
	philo = file_struc(philo, &info, av);
	start_philo(philo);
	free(philo);
	return (0);
}
