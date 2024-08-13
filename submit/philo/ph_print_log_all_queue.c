/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_print_log_all_queue.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:58:11 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/13 21:58:11 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

void	ph_print_log_all_queue(t_action_queue *queue)
{
	t_log_info	info;
	while (queue->size > 0)
	{
		ph_dequeue(queue, &info);
		ph_logging(&info.tv, info.no, info.action);
	}
	return ;
}
