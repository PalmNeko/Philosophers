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

int	ph_print_queue(t_manager *manager);

void	*ph_routine_print(t_manager *manager)
{
	bool	in_progress;
	int		queue_size;

	in_progress = true;
	while (in_progress)
	{
		pthread_mutex_lock(&manager->lock);
		pthread_mutex_lock(&manager->action_queue->lock);
		in_progress = manager->in_process;
		queue_size = manager->action_queue->size;
		pthread_mutex_unlock(&manager->lock);
		pthread_mutex_unlock(&manager->action_queue->lock);
		if (queue_size == 0)
			usleep(0);
		if (ph_print_queue(manager) == -1)
			return (NULL);
	}
	return (NULL);
}

int	ph_print_queue(t_manager *manager)
{
	t_action_queue	*cloned;
	t_log_info		del_info;

	pthread_mutex_lock(&manager->action_queue->lock);
	cloned = ph_clone_queue(manager->action_queue);
	while (cloned != NULL && manager->action_queue->size > 0)
		ph_dequeue(manager->action_queue, &del_info);
	pthread_mutex_unlock(&manager->action_queue->lock);
	if (cloned == NULL)
		return (-1);
	ph_print_log_all_queue(&manager->start, cloned);
	ph_destroy_queue(cloned);
	return (0);
}
