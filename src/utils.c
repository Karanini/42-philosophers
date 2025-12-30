/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:05:16 by bkaras-g          #+#    #+#             */
/*   Updated: 2025/12/30 15:34:26 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

/*
 * modified function for the philosophers project. Changes:
 * - no whitespace checking before the number to convert
 * - returns -1 if the number is negative (negative number not valid for philo)
 * - returns -2 if the number is `> INT_MAX / 1000`
 * - returns -3 if the number has two or more `+` or `-` signs
 *
 * Why `INT_MAX / 1000` ? The arguments are bound to be used with `usleep()`
 * function which accepts numbers to `INT_MAX`. `usleep()` takes an arg
 * in microseconds and the input args of philo are given in ms
 * so the input args have to be `< INT_MAX / 1000`
 */
int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		sign;
	int		res;

	i = 0;
	sign = 1;
	res = 0;
	if ((nptr[i] == '-' || nptr[i] == '+') && (nptr[i + 1] == '-' || nptr[i
			+ 1] == '+'))
		return (-3);
	if (nptr[i] == '-')
		return (-1);
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res *= 10;
		res += nptr[i] - '0';
		if (res > INT_MAX / 1000)
			return (-2);
		i++;
	}
	return (res * sign);
}

int	ft_check_death_flag(t_data *data)
{
	pthread_mutex_lock(&data->death_flag_mtx);
	if (data->death_flag == 1)
	{
		pthread_mutex_unlock(&data->death_flag_mtx);
		return (1);
	}
	pthread_mutex_unlock(&data->death_flag_mtx);
	return (0);
}

void	ft_raise_death_flag(t_data *data)
{
	pthread_mutex_lock(&data->death_flag_mtx);
	data->death_flag = 1;
	pthread_mutex_unlock(&data->death_flag_mtx);
}
