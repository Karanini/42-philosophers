/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wisdom_lovers_life.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:30:53 by michel_32         #+#    #+#             */
/*   Updated: 2025/12/29 11:46:37 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

static int		ft_think(t_philo *philo);

void	*ft_wise_life(void *philo_struct)
{
	t_data	*data;
	t_philo	*philo;
	int		philo_id;

	philo = (t_philo *)philo_struct;
	data = philo->data;
	philo_id = philo->philo_id;
	pthread_mutex_lock(&data->starting_mtx);
	pthread_mutex_unlock(&data->starting_mtx);
	philo->start_time = data->philo_tab[0].start_time;
	if (philo->philo_id % 2 == 0)
		ft_precise_usleep(1000);
	while (ft_check_death_flag(data) == 0)
	{
		if (ft_eat(philo) == -1)
			break ;
		if (ft_check_death_flag(data) == 1)
			break ;
		ft_print_msg(philo, SLEEP);
		if (ft_wait_and_check(philo, data->input_args->time_to_sleep * 1000)
			== -1)
			break ;
		if (ft_check_death_flag(data) == 1)
			break ;
		if (ft_think(philo) == -1)
			break ;
		// ft_print_msg(philo, THINK);
	}
	return (NULL);
}

static int		ft_think(t_philo *philo)
{
	int	time_to_think;

	time_to_think = 0;
	ft_print_msg(philo, THINK);
	if (philo->data->input_args->num_of_philos % 2 == 1 &&
	philo->data->input_args->time_to_die > (2 * philo->data->input_args->time_to_sleep + philo->data->input_args->time_to_eat))
	{
		time_to_think = (2 * philo->data->input_args->time_to_eat - philo->data->input_args->time_to_sleep);
		if (time_to_think < 0)
		time_to_think = 0;
		if (ft_wait_and_check(philo, time_to_think * 1000) == -1)
			return (-1);
	}
	return (0);
}

void	ft_print_msg(t_philo *philo, t_print_msg_type msg_type)
{
	pthread_mutex_lock(&philo->data->print_mtx);
	if (ft_check_death_flag(philo->data) == 0 || msg_type == DIE)
	{
		if (msg_type == FORK)
			printf("%lld %d has taken a fork\n", ft_get_time(),
				philo->philo_id);
		else if (msg_type == EAT)
			printf("%lld %d is eating\n", ft_get_time(), philo->philo_id);
		else if (msg_type == SLEEP)
			printf("%lld %d is sleeping\n", ft_get_time(), philo->philo_id);
		else if (msg_type == THINK)
			printf("%lld %d is thinking\n", ft_get_time(), philo->philo_id);
		else if (msg_type == DIE)
			printf("%lld %d died\n", ft_get_time(), philo->philo_id);
	}
	pthread_mutex_unlock(&philo->data->print_mtx);
}

void	ft_lock_forks(t_philo *philo, pthread_mutex_t *first_fork,
		pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(first_fork);
	ft_print_msg(philo, FORK);
	pthread_mutex_lock(second_fork);
	ft_print_msg(philo, FORK);
}

int	ft_eat(t_philo *philo)
{
	if (philo->philo_id % 2 == 1)
	{
		ft_lock_forks(philo, philo->right_fork, philo->left_fork);
		ft_print_msg(philo, EAT);
		philo->start_time = ft_get_time();
		if (ft_wait_and_check(philo, philo->data->input_args->time_to_eat
				* 1000) == -1)
			return (pthread_mutex_unlock(philo->left_fork),
				pthread_mutex_unlock(philo->right_fork), -1);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		ft_lock_forks(philo, philo->left_fork, philo->right_fork);
		ft_print_msg(philo, EAT);
		philo->start_time = ft_get_time();
		if (ft_wait_and_check(philo, philo->data->input_args->time_to_eat
				* 1000) == -1)
			return (pthread_mutex_unlock(philo->right_fork),
				pthread_mutex_unlock(philo->left_fork), -1);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	return (0);
}
