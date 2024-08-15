/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_new_action_queue.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 20:54:10 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/13 20:54:10 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

t_action_queue	*ph_new_queue(int init_size)
{
	t_action_queue	*queue;

	queue = (t_action_queue *)malloc(sizeof(t_action_queue));
	if (queue == NULL)
		return (NULL);
	memset(queue, 0, sizeof(t_action_queue));
	queue->infos = (t_log_info *)malloc(sizeof(t_log_info) * init_size);
	if (queue->infos == NULL)
		return (ph_destroy_queue(queue), NULL);
	queue->top = 0;
	queue->bottom = 0;
	queue->size = 0;
	pthread_mutex_init(&queue->lock, NULL);
	queue->max_size = init_size;
	return (queue);
}
