/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_new_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:01:21 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/13 17:01:21 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_types.h"
#include <string.h>
#include <stdlib.h>

t_manager	*ph_new_manager(
		int time_to_die,
		int time_to_eat,
		int time_to_sleep,
		int must_eat_times)
{
	t_manager	*manager;

	manager = (t_manager *)malloc(sizeof(t_manager));
	if (manager == NULL)
		return (NULL);
	memset(manager, 0, sizeof(t_manager));
	manager->time_to_die = time_to_die;
	manager->time_to_eat = time_to_eat;
	manager->time_to_sleep = time_to_sleep;
	manager->must_eat_times = must_eat_times;
	return (manager);
}
