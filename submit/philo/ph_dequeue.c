/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_dequeue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:12:16 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/13 21:12:16 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_types.h"

int	ph_dequeue(t_action_queue *queue, t_log_info *info)
{
	if (queue->size == 0)
		return (-1);
	*info = queue->infos[queue->top];
	queue->top += 1;
	queue->top %= queue->max_size;
	queue->size -= 1;
	return (0);
}
