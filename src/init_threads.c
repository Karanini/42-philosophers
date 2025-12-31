/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:02:41 by bkaras-g          #+#    #+#             */
/*   Updated: 2025/12/31 09:32:34 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

static int	ft_init_philo_threads(t_data *data);

/*
* initializing the philosophers' threads and the monitor thread.
* The `starting_mtx` mutex is
* locked by the main thread, then by all the other threads
* as soon as they are created so that each thread waits until
* all the threads have been created before starting the simulation.
*
* If a thread init fails and one or more other threads have already been
* created, `death_flag` is set to 1 to make the other threads terminate.
* In this case, the mutexes destroying and memory cleanup is made
* by `ft_cleanup` in main.
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

/*
* initialization of the philosophers threads. Two cases:
* - If only one philosopher, assigning the routine `ft_solitary_life`
* - If two or more philos, assigning the routine `ft_wise_life`
*/
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
