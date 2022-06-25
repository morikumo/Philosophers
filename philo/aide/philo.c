/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabid <mabid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:13:49 by benmoham          #+#    #+#             */
/*   Updated: 2022/06/25 19:35:22 by mabid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*routine(void *argv)
{
	t_utils_philo	*philo;

	philo = (t_utils_philo *)argv;
	while (check_stop(philo->info) == 0) // Verifie la disponbiliter du mutex  
		take_fork(philo); // Une fois que le mutex est disponible on take_fork
	return (NULL); // Return NULL si take fork c'est mal passer, et par consequant renvoit NULL au pthread create qui n'enverra vers rien 
}

/**
 * @brief Va fermer les mutex et les thread
 * 
 * @param philo 
 */
void	finish_prog(t_utils_philo *philo)
{
	int	i;

	i = 0;
	while (check_stop(philo->info) == 0)
	{
		if (check_dead(&philo[i]) == 0 || check_eat(philo) == 0)
		{
			i = 0;
			while (i < philo->info->nb_philo)
			{
				pthread_join(philo[i].thread, NULL); // Return NULL va fermer le thread en les initialisant a NULL
				i++;
			}
			i = -1;
			while (++i < philo->info->nb_philo) // Il y a le meme nombre de fourchette que de philo, il faut donc fermer tout les mutex
				pthread_mutex_destroy(&philo[i].left_fork); 
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
	int	i;

	i = 0;
	while (i < philo->info->nb_philo) 
	{
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]); // Va creer un thread par philo et lancer la routine
		usleep(2000); // Va patienter apres chaque signal de thread le temps de recevoir les info ect pour pas avoir de mort direct 
		i++;
	}
	finish_prog(philo); // Finish_prog va fermer tout le mutex et thread en cours, si il y a une erreur
}

void	start_philo(t_utils_philo *philo)
{
	philo->info->start_time = actual_time(); // Recupere la variable de temps et a pour objectif de l'afficher sur le cote
	pthread_mutex_init(&philo->info->write_mutex, NULL); // Initialisation de chaque mutex
	pthread_mutex_init(&philo->info->death_mutex, NULL); // ''''
	pthread_mutex_init(&philo->info->eat_mutex, NULL); // ''''
	pthread_mutex_init(&philo->info->stop_mutex, NULL); // ''''
	create_thread(philo); // Ici commence le processus des thread par la variable philo qui est aussi une structure
}
