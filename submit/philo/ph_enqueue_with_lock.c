/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_enqueue_with_lock.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:32:06 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/13 21:32:06 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <unistd.h>

int	ph_enqueue_with_lock(t_action_queue *queue, int no, t_philo_action action)
{
	int			error;
	int			result;

	while ((queue->size >= queue->max_size - queue->max_size / 2))
		usleep(0);
	error = pthread_mutex_lock(&queue->lock);
	if (error != 0)
		return (error);
	result = ph_enqueue(queue, no, action);
	error = pthread_mutex_unlock(&queue->lock);
	if (error != 0)
		return (error);
	if (result > 0)
		return (result);
	return (0);
}
