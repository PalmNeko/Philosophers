/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_dequeue_with_lock.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:30:27 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/13 21:30:27 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <pthread.h>

int	ph_dequeue_with_lock(t_action_queue *queue, t_log_info *info)
{
	int			error;
	int			result;

	error = pthread_mutex_lock(&queue->lock);
	if (error != 0)
		return (error);
	result = ph_dequeue(queue, info);
	error = pthread_mutex_unlock(&queue->lock);
	if (error != 0)
		return (error);
	if (result > 0)
		return (result);
	return (0);
}
