/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabid <mabid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:30:33 by mabid             #+#    #+#             */
/*   Updated: 2022/07/07 14:53:18 by mabid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	ft_atol(char *str)
{
	int		i;
	int		neg;
	long	res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] == '\f' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\n' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = neg * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * neg);
}

int	ft_isdigit(char s)
{
	if (s >= '0' && s <= '9')
		return (0);
	else
		return (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_max(char *av)
{
	if (ft_atol(av) > INT_MAX || ft_atol(av) < INT_MIN
		|| ft_strlen(av) == 0 || ft_atol(av) == 0)
	{
		printf("bad character\n");
		return (1);
	}
	return (0);
}

/**
 * @brief Va verifier si les parametres sont corrects, dans la chaine de caractere av
 * 
 * @param av 
 * @return int 
 */
int	check_arg(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		if (check_max(av[i]) == 1)
			return (1);
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]) == 1 || ft_atol(av[1]) > 200
					|| av[i][j] == '-')
			{
				printf("bad character\n");
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
