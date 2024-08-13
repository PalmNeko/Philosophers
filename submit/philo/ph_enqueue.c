/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_enqueue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:00:05 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/13 21:00:05 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_types.h"
#include <errno.h>
#include <sys/time.h>

int	ph_enqueue(t_action_queue *queue, int no, t_philo_action action)
{
	if (queue->size == queue->max_size)
		return (ENOMEM);
	queue->infos[queue->bottom] = (t_log_info){.action = action, .no = no};
	gettimeofday(&queue->infos[queue->bottom].tv, NULL);
	queue->bottom += 1;
	queue->bottom &= queue->max_size;
	queue->size += 1;
	return (0);
}
