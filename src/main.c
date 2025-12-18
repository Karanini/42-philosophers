/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:40:37 by bkaras-g          #+#    #+#             */
/*   Updated: 2025/12/18 11:44:10 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	main(int ac, char *av[])
{
	t_data	*data;

	if (ac < 4 || ac > 5)
	{
		printf("incorrect number of arguments\n");
		return (1);
	}
	data = ft_init_data(ac, av);
	ft_init_threads(data);
	if (!data)
		return (1);
	return (0);
}
