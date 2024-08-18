/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_wait_once.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:51:22 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/16 16:51:22 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include "ph_defs.h"

unsigned int	ph_calc_wait_time(struct timeval *subtvp);

/**
 * the usleep has accuracy so `usleep(sleep_time_usec - TIMER_ACCURACY_USEC)`
 */
int	ph_wait_once(struct timeval *nowtvp, struct timeval *endtvp)
{
	struct timeval	sub;
	unsigned int	sleep_time_usec;

	if (timercmp(nowtvp, endtvp, <))
	{
		timersub(endtvp, nowtvp, &sub);
		sleep_time_usec = ph_calc_wait_time(&sub);
		return (usleep(sleep_time_usec));
	}
	return (0);
}

/**
 * TODO: If remove sleep_time_usec variable more fast than no-remove one,
 * you should remove it.
 */
unsigned int	ph_calc_wait_time(struct timeval *subtvp)
{
	unsigned int	sleep_time_usec;

	if (subtvp->tv_sec >= 2)
		sleep_time_usec = 1000000 + TIMER_ACCURACY_USEC;
	else
		sleep_time_usec = subtvp->tv_sec * 1000000 + subtvp->tv_usec;
	if (sleep_time_usec > 1000000 + TIMER_ACCURACY_USEC)
		sleep_time_usec = 1000000;
	else if (sleep_time_usec > TIMER_ACCURACY_USEC)
		sleep_time_usec = sleep_time_usec - TIMER_ACCURACY_USEC;
	else
		sleep_time_usec = 0;
	return (sleep_time_usec);
}
