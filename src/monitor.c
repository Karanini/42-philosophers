/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 17:16:23 by bkaras-g          #+#    #+#             */
/*   Updated: 2025/12/28 17:29:14 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_monitoring(void *data_struct)
{
	t_data			*data;
	int				i;
	struct timeval	current;

	data = (t_data *)data_struct;
	i = 0;
	while (1)
	{
		while (i < data->input_args->num_of_philos)
		{
			if (ft_get_time()
				- data->philo_tab[i].start_time > data->input_args->time_to_die)
			{
				pthread_mutex_lock(&data->death_flag_mtx);
				data->death_flag = 1;
				pthread_mutex_unlock(&data->death_flag_mtx);
				return (NULL);
			}
			i++;
		}
		i = 0;
	}
	return (NULL);
}
