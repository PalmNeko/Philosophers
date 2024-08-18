/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_destroy_queue.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 20:57:03 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/13 20:57:03 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_types.h"
#include <stdlib.h>
#include <pthread.h>

void	ph_destroy_queue(t_action_queue *queue)
{
	if (queue == NULL)
		return ;
	pthread_mutex_destroy(&queue->lock);
	free(queue->infos);
	free(queue);
	return ;
}
