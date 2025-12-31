/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 11:06:57 by bkaras-g          #+#    #+#             */
/*   Updated: 2025/12/31 11:33:57 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

long	ft_get_elapsed_time_microseconds(struct timeval start,
		struct timeval end)
{
	return ((end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec
			- start.tv_usec));
}

/*

	* usleep() guarantees a minimum time of sleep but generally makes
	the thread sleep more than asked (approx. 70 ms). To avoid this,
	this function usleeps in chunks
 * and computes the actual elapsed time. When rem <= 100,
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
		if (rem > 100)
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
 * @brief waits 5 ms with `ft_precise_usleep` then checks if `death_flag`
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
		ft_precise_usleep(5 * 1000);
		if (ft_check_death_flag(philo->data) == 1)
			return (-1);
		gettimeofday(&current, NULL);
		elapsed = ft_get_elapsed_time_microseconds(start, current);
	}
	return (0);
}
