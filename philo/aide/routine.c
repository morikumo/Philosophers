/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabid <mabid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:47:31 by benmoham          #+#    #+#             */
/*   Updated: 2022/06/25 19:52:03 by mabid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	display_msg(t_utils_philo *philo, char *msg, int check_die)
{
	int	die;

	pthread_mutex_lock(&philo->info->write_mutex);
	die = 0;
	if (die == 0)
	{
		if (check_die == 1)
			die = 1;
		if (check_stop(philo->info) != 1)
			printf("%ld %d %s",
				actual_time() - philo->info->start_time, philo->id, msg);
		pthread_mutex_unlock(&philo->info->write_mutex);
	}
	else
		pthread_mutex_unlock(&philo->info->write_mutex);
}

void
	mutex_fork(t_utils_philo *philo, pthread_mutex_t *rf, pthread_mutex_t *lf)
{
	pthread_mutex_lock(lf); // Lorsque lf est lock
	display_msg(philo, FORK, 0); // On affiche le message qu'une fourchette est prise
	pthread_mutex_lock(rf); // La deuxieme fourchette est lock
	display_msg(philo, FORK, 0); // On affiche le msg
	display_msg(philo, EAT, 0); // Vu que l'on a les 2 fourchettes on peut manger
	pthread_mutex_lock(&philo->info->death_mutex); // Puisqu'il mange il ne peut pas mourir donc on lock la mort
	philo->last_meal = actual_time() - philo->info->start_time; // On retire le temps de manger et on recalcule 
	pthread_mutex_unlock(&philo->info->death_mutex); // Une fois fait on unlock la mort pour voir si quelqu'un est eligible a la mort
	pthread_mutex_lock(&philo->info->eat_mutex); // Ensuite seulement il mange, on lock la bouffe
	if (philo->to_eat < philo->info->nb_eat) // C'est pour le cas argv [5] on augemente la variable de la limite de repas
		philo->to_eat++;
	if (philo->to_eat == philo->info->nb_eat && philo->info->nb_eat != 0) // Si la limite de repas est atteinte on augemente la variable finish_eat pour arreter
		philo->info->finish_eat++;
	pthread_mutex_unlock(&philo->info->eat_mutex); // On unlock le mutex bouffe
	ft_usleep(philo->info->time_eat, philo->info); // Usleep pour gerer les info, delock tt ect
	pthread_mutex_unlock(rf);
	pthread_mutex_unlock(lf);
	display_msg(philo, SLEEP, 0);
	ft_usleep(philo->info->time_sleep, philo->info);
	display_msg(philo, THINK, 0);
}

void	take_fork(t_utils_philo *philo)
{
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;

	l_fork = &philo->left_fork; // On donne l'addresse de la fourchette de gauche mais les 2 peuvent bouger, on commence par donner la gauche
	r_fork = philo->right_fork; // On ne donne pas l'adresse pour la fourchette de droite
	if (philo->info->nb_philo == 1) // Si nous avons qu'un seul philo, il prend la fourchette, affiche le msg, meurt et libere le mutex
	{
		pthread_mutex_lock(&philo->left_fork);
		display_msg(philo, FORK, 0); // Permet d'afficher les messages 
		ft_usleep(philo->info->time_die, philo->info); // Force la mort d'un philo
		pthread_mutex_unlock(&philo->left_fork);
		return ; // Salam
	}
	if (philo->id == philo->info->nb_philo) 
	{
		l_fork = philo->right_fork;
		r_fork = &philo->left_fork;
	}
	mutex_fork(philo, r_fork, l_fork);
}
