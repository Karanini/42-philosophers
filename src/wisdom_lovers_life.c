/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wisdom_lovers_life.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:30:53 by michel_32         #+#    #+#             */
/*   Updated: 2025/12/18 13:49:21 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void    *ft_wise_life(void *philo_struct)
{
	t_data	*data;
	t_philo	*philo;
	int	philo_id;

	philo = (t_philo *) philo_struct;
	data = philo->data;
	philo_id = philo->philo_id;
	pthread_mutex_lock(&data->starting_mtx);
	pthread_mutex_unlock(&data->starting_mtx);

	printf("philosopher %d IS ALIIIIVE\n", philo_id);
	//eat
	//sleep
	//think
	return (NULL);
}
