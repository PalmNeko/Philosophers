/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_clone_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:47:53 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/13 21:47:53 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <stdlib.h>

t_action_queue	*ph_clone_queue(t_action_queue *queue)
{
	t_action_queue	*cloned;
	size_t			index;

	cloned = ph_new_queue(queue->max_size);
	if (cloned == NULL)
		return (NULL);
	index = 0;
	while (index < queue->max_size)
	{
		cloned->infos[index] = queue->infos[index];
		index++;
	}
	return (cloned);
}
