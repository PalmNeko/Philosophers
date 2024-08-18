/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_generate_philosophers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:09:13 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/18 14:10:17 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <stdlib.h>
#include <string.h>

t_philosopher	*ph_generate_philosophers(t_manager *manager)
{
	t_philosopher	*philos;
	int				index;
	int				size;

	size = sizeof(t_philosopher) * manager->philo_cnt;
	philos = (t_philosopher *)malloc(size);
	if (philos == NULL)
		return (NULL);
	memset(philos, 0, size);
	index = 0;
	while (index < manager->philo_cnt)
	{
		memset(&philos[index], 0, sizeof(t_philosopher));
		philos[index] = (t_philosopher){
			.in_process = true,
			.manager = manager,
			.last_eat = manager->start,
			.no = index + 1,
		};
		pthread_mutex_init(&philos[index].fork, NULL);
		pthread_mutex_init(&philos[index].lock, NULL);
		index++;
	}
	return (philos);
}
