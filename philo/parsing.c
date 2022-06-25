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

int	ft_isdigit(char str)
{
	if (str >= '0' && str <= '9')
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

int	check_max(char *argv)
{
	if (ft_atol(argv) > INT_MAX || ft_atol(argv) < INT_MIN
		|| ft_strlen(argv) == 0 || ft_atol(argv) == 0)
	{
		printf("bad character\n");
		return (1);
	}
	return (0);
}

int	check_arg(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		if (check_max(argv[i]) == 1)
			return (1);
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 1 || ft_atol(argv[1]) > 200
					|| argv[i][j] == '-')
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