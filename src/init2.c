/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:21:11 by michel_32         #+#    #+#             */
/*   Updated: 2025/12/28 16:25:39 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	ft_init_mutexes(t_data *data)
{
	if (ft_single_mutex_init(&data->print_mtx) == -1)
		return (-1);
	if (ft_single_mutex_init(&data->starting_mtx) == -1)
		return (-1);
	if (ft_single_mutex_init(&data->death_flag_mtx) == -1)
		return (-1);
	data->fork_mtx = ft_init_fork_mutexes(data->input_args->num_of_philos);
	if (!data->fork_mtx)
		return (-1);
	return (0);
}

int	ft_single_mutex_init(pthread_mutex_t *mutex)
{
	int	ret;

	ret = pthread_mutex_init(mutex, NULL);
	if (ret != 0)
		return (-1);
	return (0);
}

/*
* initializing the philosophers' threads. The `starting_mtx` mutex is
* locked by the main thread, then by all the other created threads
* in ft_wise_life() so that each thread waits until all the threads
* have been created.

* to do if a thread init fails:
* //death_flag = 1;
//unlock starting mutex
* destroy the mutexes and cleanup the memory
*/
int	ft_init_threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->starting_mtx);
	while (i < data->input_args->num_of_philos)
	{
		if (pthread_create(&data->philo_tab[i].tid, NULL, &ft_wise_life,
				&data->philo_tab[i]) != 0)
			return (-1);
		i++;
	}
	data->philo_tab[0].start_time = ft_get_time();
	pthread_mutex_unlock(&data->starting_mtx);
	return (0);
}

