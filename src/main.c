/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:40:37 by bkaras-g          #+#    #+#             */
/*   Updated: 2025/12/18 13:26:39 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	main(int ac, char *av[])
{
	t_data	*data;
	int		i;

	if (ac < 4 || ac > 5)
	{
		printf("incorrect number of arguments\n");
		return (1);
	}
	data = ft_init_data(ac, av);
	ft_init_threads(data);
	if (!data)
		return (1);
	i = 0;
	while (i < data->input_args->number_of_philosophers)
	{
		if (pthread_join(data->philo_tab[i].tid, NULL) != 0)
			return (ft_cleanup(data), 1);
		i++;
	}
	ft_cleanup(data);
	return (0);
}
