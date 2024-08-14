/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:46:54 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/13 21:46:54 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <pthread.h>
#include <unistd.h>

void	*ph_routine_print(t_manager *manager)
{
	t_action_queue	*cloned;
	t_log_info		del_info;
	struct timeval	start;
	int				error;

	while (manager->in_process)
	{
		if (manager->action_queue->size <= 1 && manager->in_process)
			ph_msleep(5);
		error = pthread_mutex_lock(&manager->action_queue->lock);
		if (error != 0)
			return (NULL);
		cloned = ph_clone_queue(manager->action_queue);
		if (cloned != NULL)
		{
			while (manager->action_queue->size > 0)
				ph_dequeue(manager->action_queue, &del_info);
		}
		error = pthread_mutex_unlock(&manager->action_queue->lock);
		if (cloned == NULL || error != 0)
			return (NULL);
		start = manager->start;
		ph_print_log_all_queue(&start, cloned);
		ph_destroy_queue(cloned);
	}
	return (NULL);
}
