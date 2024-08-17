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
	bool	in_progress;

	while (1)
	{
		pthread_mutex_lock(&manager->lock);
		in_progress = manager->in_process;
		gettimeofday(&manager->now, NULL);
		pthread_mutex_unlock(&manager->lock);
		if (in_progress == false)
			break ;
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
