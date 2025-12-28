/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:26:35 by bkaras-g          #+#    #+#             */
/*   Updated: 2025/12/28 17:33:31 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	ft_free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->input_args)
		free(data->input_args);
	if (data->philo_tab)
		free(data->philo_tab);
	if (data->fork_mtx)
		free(data->fork_mtx);
	free(data);
}

void	ft_cleanup(t_data *data)
{
	int	i;

	if (!data)
		return ;
	pthread_mutex_destroy(&data->print_mtx);
	pthread_mutex_destroy(&data->starting_mtx);
	pthread_mutex_destroy(&data->death_flag_mtx);
	if (data->fork_mtx)
	{
		i = 0;
		while (i < data->input_args->num_of_philos)
		{
			pthread_mutex_destroy(&data->fork_mtx[i]);
			i++;
		}
	}
	ft_free_data(data);
}
