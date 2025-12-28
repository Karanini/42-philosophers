/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 17:16:23 by bkaras-g          #+#    #+#             */
/*   Updated: 2025/12/28 19:31:07 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	*ft_monitoring(void *data_struct)
{
	t_data			*data;
	int				i;

	data = (t_data *)data_struct;
	i = 0;
	pthread_mutex_lock(&data->starting_mtx);
	pthread_mutex_unlock(&data->starting_mtx);
	while (1)
	{
		while (i < data->input_args->num_of_philos)
		{
			if (ft_get_time()
				- data->philo_tab[i].start_time > data->input_args->time_to_die)
			{
				ft_print_msg(&data->philo_tab[i], DIE);
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
