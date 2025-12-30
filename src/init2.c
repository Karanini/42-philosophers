/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:21:11 by michel_32         #+#    #+#             */
/*   Updated: 2025/12/30 13:53:33 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

static int	ft_init_philo_threads(t_data *data);

int	ft_init_mutexes(t_data *data)
{
	if (ft_single_mutex_init(&data->print_mtx) == -1)
		return (-1);
	if (ft_single_mutex_init(&data->starting_mtx) == -1)
		return (pthread_mutex_destroy(&data->print_mtx), -1);
	if (ft_single_mutex_init(&data->death_flag_mtx) == -1)
	{
		pthread_mutex_destroy(&data->print_mtx);
		pthread_mutex_destroy(&data->starting_mtx);
		return (-1);
	}
	data->fork_mtx = ft_init_fork_mutexes(data->input_args->num_of_philos);
	if (!data->fork_mtx)
	{
		pthread_mutex_destroy(&data->print_mtx);
		pthread_mutex_destroy(&data->starting_mtx);
		pthread_mutex_destroy(&data->death_flag_mtx);
		return (-1);
	}
	// if (ft_init_meal_mutexes(data) == -1)
	// {
	// 	pthread_mutex_destroy(&data->print_mtx);
	// 	pthread_mutex_destroy(&data->starting_mtx);
	// 	pthread_mutex_destroy(&data->death_flag_mtx);
	// 	ft_destroy_fork_mutexes(data);
	// }
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
	pthread_mutex_lock(&data->starting_mtx);
	if (ft_init_philo_threads(data) == -1)
	{
		pthread_mutex_unlock(&data->starting_mtx);
		return (-1);
	}
	if (pthread_create(&data->monitor_tid, NULL, &ft_monitoring, data) != 0)
	{
		data->death_flag = 1;
		pthread_mutex_unlock(&data->starting_mtx);
		return (-1);
	}
	data->sim_start_time = ft_get_time();
	pthread_mutex_unlock(&data->starting_mtx);
	return (0);
}

static int	ft_init_philo_threads(t_data *data)
{
	int	i;

	i = 0;
	if (data->input_args->num_of_philos == 1)
	{
		if (pthread_create(&data->philo_tab[0].tid, NULL, &ft_solitary_life,
				&data->philo_tab[0]) != 0)
			return (-1);
	}
	else
	{
		while (i < data->input_args->num_of_philos)
		{
			if (pthread_create(&data->philo_tab[i].tid, NULL, &ft_wise_life,
					&data->philo_tab[i]) != 0)
				return (data->death_flag = 1, -1);
			i++;
		}
	}
	return (0);
}
