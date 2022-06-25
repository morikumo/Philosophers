/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:22:36 by mdouiri           #+#    #+#             */
/*   Updated: 2022/06/12 16:22:43 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr_u(u_int64_t nb)
{
	if (nb >= 10)
	{
		ft_putnbr_u(nb / 10);
		ft_putnbr_u(nb % 10);
	}
	else
		ft_putchar(nb % 10 + 48);
}

void	display(long long time, int id, int states)
{
	static char	*msg[5] = {
		" is thinking\n",
		" is eating\n",
		" has taken a fork\n",
		" is dead\n",
		" is sleeping\n",
	};
	static int	size[5] = {
		13,
		11,
		18,
		9,
		13,
	};

	ft_putnbr_u(time);
	write(1, " Philosopher ", 14);
	ft_putnbr_u(id);
	write(1, msg[states], size[states]);
}
