/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:21:11 by michel_32         #+#    #+#             */
/*   Updated: 2025/12/18 11:51:45 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	ft_mutex_init(pthread_mutex_t mutex)
{
	int	ret;

	ret = pthread_mutex_init(&mutex, NULL);
	if (ret != 0)
		return (-1);
	return (0);
}

int	ft_init_threads(t_data *data)
{
	int i;

	i = 0;
	if (ft_mutex_init(data->starting_mtx) == -1)
		return (-1);
	pthread_mutex_lock(&data->starting_mtx);
	while (i < data->input_args->number_of_philosophers)
	{
		data->philo_id = i;
		if (pthread_create(&data->philo_tab[i].tid, NULL, &ft_wise_life,
				data) != 0)
			return (-1);
		i++;
	}
	//initialize the start_time here
	pthread_mutex_unlock(&data->starting_mtx);
	return (0);
}
