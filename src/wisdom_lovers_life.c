/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wisdom_lovers_life.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:30:53 by michel_32         #+#    #+#             */
/*   Updated: 2025/12/25 17:42:27 by bkaras-g         ###   ########.fr       */
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
	philo->start_time = data->philo_tab[0].start_time;
	printf("philosopher %d IS ALIIIIVE\n", philo_id);
	ft_eat(philo);
	//eat
	//sleep
	//think
	return (NULL);
}

void	ft_eat(t_philo *philo)
{
	if (philo->philo_id % 2 == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		ft_print_msg(philo, FORK);
		pthread_mutex_lock(philo->left_fork);
		ft_print_msg(philo, FORK);
		ft_print_msg(philo, EAT);
		philo->start_time = ft_get_time();
		ft_precise_usleep(philo->data->input_args->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print_msg(philo, FORK);
		pthread_mutex_lock(philo->right_fork);
		ft_print_msg(philo, FORK);
		ft_print_msg(philo, EAT);
		philo->start_time = ft_get_time();
		ft_precise_usleep(philo->data->input_args->time_to_eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}
