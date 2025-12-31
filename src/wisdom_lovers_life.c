/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wisdom_lovers_life.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:30:53 by michel_32         #+#    #+#             */
/*   Updated: 2025/12/31 11:45:21 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

static int	ft_think(t_philo *philo);
static int	ft_eat_sleep_think(t_philo *philo);

void	*ft_wise_life(void *philo_struct)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	data = philo->data;
	pthread_mutex_lock(&data->starting_mtx);
	pthread_mutex_unlock(&data->starting_mtx);
	pthread_mutex_lock(&philo->meal_mtx);
	philo->start_time = data->sim_start_time;
	pthread_mutex_unlock(&philo->meal_mtx);
	if (philo->philo_id % 2 == 0)
		ft_precise_usleep(1000);
	while (ft_check_death_flag(data) == 0)
	{
		if (ft_eat_sleep_think(philo) == -1)
			break ;
	}
	return (NULL);
}

static int	ft_eat_sleep_think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (ft_eat(philo) == -1)
		return (-1);
	if (ft_check_death_flag(data) == 1)
		return (-1);
	ft_print_msg(philo, SLEEP);
	if (ft_wait_and_check(philo, data->input_args->time_to_sleep * 1000)
		== -1)
		return (-1);
	if (ft_check_death_flag(data) == 1)
		return (-1);
	if (ft_think(philo) == -1)
		return (-1);
	return (0);
}

/*
* If uneven number of philosophers, need to implement a `time_to_think`
* to avoid a philo to starve because he does not manage to grab the forks
* before his neighboors.

* A philosopher must wait for his 2 neighbors to eat before it is his
* turn again. So need to have the cycle respecting `time_to_sleep +
* time_to_think = 2 * time_to_eat`.
* Hence `time_to_think = (2 * time_to_eat - time_to_sleep)`
*
* Also, need to check if the philosophers have the time to be polite
* to let their neighbors eat:
* `Total Cycle=Eat+Sleep+Think`
* `Total Cycle=Eat+Sleep+(2×Eat−Sleep)=3×Eat`
* So need to check `if time_to_die > (3 * time_to_eat)` before assigning
* a thinking time, so that we are sure that the philosopher can have
* a thinking time without starving.
*/
static int	ft_think(t_philo *philo)
{
	int	time_to_think;
	int	time_to_die;
	int	time_to_sleep;
	int	time_to_eat;

	ft_print_msg(philo, THINK);
	time_to_die = philo->data->input_args->time_to_die;
	time_to_sleep = philo->data->input_args->time_to_sleep;
	time_to_eat = philo->data->input_args->time_to_eat;
	if (philo->data->input_args->num_of_philos % 2 == 1 && time_to_die > (3
			* time_to_eat))
	{
		time_to_think = (2 * time_to_eat - time_to_sleep);
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
			printf("%lld %d has taken a fork\n", ft_get_time()
				- philo->data->sim_start_time, philo->philo_id);
		else if (msg_type == EAT)
			printf("%lld %d is eating\n", ft_get_time()
				- philo->data->sim_start_time, philo->philo_id);
		else if (msg_type == SLEEP)
			printf("%lld %d is sleeping\n", ft_get_time()
				- philo->data->sim_start_time, philo->philo_id);
		else if (msg_type == THINK)
			printf("%lld %d is thinking\n", ft_get_time()
				- philo->data->sim_start_time, philo->philo_id);
		else if (msg_type == DIE)
			printf("%lld %d died\n", ft_get_time()
				- philo->data->sim_start_time, philo->philo_id);
	}
	pthread_mutex_unlock(&philo->data->print_mtx);
}

/*
* function to make the philosophers grab forks and eat. To avoid mutex
* deadlocks, the uneven philos grab first the right fork then the left
* one, while the even philos grab first the left one then the right one.
* If all the philos would have grabed the forks in the same order, each
* would wait eternally for impossible mutex unlocks --> deadlock
*/
int	ft_eat(t_philo *philo)
{
	if (philo->philo_id % 2 == 1)
	{
		ft_lock_forks(philo, philo->right_fork, philo->left_fork);
		ft_print_msg(philo, EAT);
		ft_grant_more_life(philo);
		if (ft_wait_and_check(philo, philo->data->input_args->time_to_eat
				* 1000) == -1)
			return (ft_unlock_forks(philo->left_fork, philo->right_fork), -1);
		ft_unlock_forks(philo->left_fork, philo->right_fork);
	}
	else
	{
		ft_lock_forks(philo, philo->left_fork, philo->right_fork);
		ft_print_msg(philo, EAT);
		ft_grant_more_life(philo);
		if (ft_wait_and_check(philo, philo->data->input_args->time_to_eat
				* 1000) == -1)
			return (ft_unlock_forks(philo->right_fork, philo->left_fork), -1);
		ft_unlock_forks(philo->right_fork, philo->left_fork);
	}
	if (philo->data->input_args->number_of_meals > 0)
		ft_mark_full_belly(philo);
	return (0);
}
