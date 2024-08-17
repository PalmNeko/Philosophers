/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_tvsleep_until.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:49:59 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/16 16:49:59 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <sys/time.h>

int	ph_tvsleep_until(struct timeval *endtime, t_manager *manager)
{
	struct timeval	now;
	bool			in_progress;

	gettimeofday(&now, NULL);
	while(timercmp(&now, endtime, <) && manager->in_process)
	{
		pthread_mutex_lock(&manager->lock);
		in_progress = manager->in_process;
		pthread_mutex_unlock(&manager->lock);
		if (in_progress == false)
			return (0);
		if (ph_wait_once(&now, endtime) == -1)
			return (-1);
		gettimeofday(&now, NULL);
	}
	return (0);
}
