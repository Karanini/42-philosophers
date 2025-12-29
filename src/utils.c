/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:05:16 by bkaras-g          #+#    #+#             */
/*   Updated: 2025/12/29 16:28:31 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

/*
* modified function for the philosophers project. Changes:
* - no whitespace checking before the number to convert
* - returns -1 if the number is negative (negative number not valid for philo)
* - returns -2 if the number is > INT_MAX
* - returns -3 if the number has two or more `+` or `-` signs
*/
int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		sign;
	int		res;

	i = 0;
	sign = 1;
	res = 0;
	if ((nptr[i] == '-' || nptr[i] == '+') && (nptr[i + 1] == '-'
			|| nptr[i + 1] == '+'))
		return (-3);
	if (nptr[i] == '-')
		return (-1);
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res *= 10;
		res += nptr[i] - '0';
		if (res > INT_MAX)
			return (-2);
		i++;
	}
	return (res * sign);
}

long	ft_get_elapsed_time_microseconds(struct timeval start,
		struct timeval end)
{
	return ((end.tv_sec - start.tv_sec) * 1000000L
		+ (end.tv_usec - start.tv_usec));
}

/*

	* usleep() guarantees a minimum time of sleep but generally makes
	the thread sleep more than asked (approx. 70 ms). To avoid this,
	this function usleeps in chunks
 * and computes the actual elapsed time. When rem <= 1000,
	the thread busy-waits: it
 * loops computing elapsed again and again until it's > usec
 *
 * @param usec the time to wait in microseconds
 */
void	ft_precise_usleep(long usec)
{
	long			elapsed;
	long			rem;
	struct timeval	start;
	struct timeval	current;

	gettimeofday(&start, NULL);
	elapsed = 0;
	while (elapsed < usec)
	{
		gettimeofday(&current, NULL);
		elapsed = ft_get_elapsed_time_microseconds(start, current);
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
	}
}

long long	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}


/**
 * @brief waits 10 ms with `ft_precise_usleep` then checks if `death_flag`
 * is set to 1, until `time_to_wait` is reached
 *
 * @param philo Pointer to the philosopher structure.
 * @param time_to_wait The total time to wait in microseconds.
 * @return -1 if the philosopher died or the simulation stopped during the wait,
 *         0 otherwise.
 */
int	ft_wait_and_check(t_philo *philo, int time_to_wait)
{
	long			elapsed;
	struct timeval	start;
	struct timeval	current;

	gettimeofday(&start, NULL);
	elapsed = 0;
	while (elapsed < (long)time_to_wait)
	{
		ft_precise_usleep(10 * 1000);
		if (ft_check_death_flag(philo->data) == 1)
			return (-1);
		gettimeofday(&current, NULL);
		elapsed = ft_get_elapsed_time_microseconds(start, current);
	}
	return (0);
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
