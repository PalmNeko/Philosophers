/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine_update_manager.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:14:13 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/15 17:14:13 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_types.h"
#include <sys/time.h>
#include <unistd.h>

void	*ph_routine_update_manager(t_manager *manager)
{
	while (manager->in_process)
	{
		gettimeofday(&manager->now, NULL);
		if (usleep(0) == -1)
		{
			pthread_mutex_lock(&manager->lock);
			manager->in_process = false;
			pthread_mutex_unlock(&manager->lock);
			return (NULL);
		}
	}
	return (NULL);
}
