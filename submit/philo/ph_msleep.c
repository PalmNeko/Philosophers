/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_busy_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 22:41:55 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/11 22:41:55 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include "ph.h"
#include "ph_defs.h"

int	ph_msleep(unsigned int msec, t_manager *manager)
{
	struct timeval	start;
	struct timeval	now;
	struct timeval	diff;
	struct timeval	endtime;

	gettimeofday(&start, NULL);
	diff = ph_msectotimeval(msec);
	timeradd(&start, &diff, &endtime);
	now = start;
	gettimeofday(&now, NULL);
	while(timercmp(&now, &endtime, <) && manager->in_process)
	{
		if (ph_wait_once(&now, &endtime) == -1)
			return (-1);
		gettimeofday(&now, NULL);
	}
	return (0);
}
