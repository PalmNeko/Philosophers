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
#include "ph_defs.h"

unsigned int	ph_timertomsc(struct timeval *tvp);
struct timeval	ph_msectotimeval(unsigned int timesec);
int				ph_wait_until(struct timeval *tvp);

int	ph_msleep(unsigned int msec)
{
	struct timeval	start;
	struct timeval	diff;
	struct timeval	endtime;

	gettimeofday(&start, NULL);
	diff = ph_msectotimeval(msec);
	timeradd(&start, &diff, &endtime);
	if (ph_wait_until(&endtime) == -1)
		return (-1);
	return (0);
}

/**
 * the usleep has accuracy so `usleep(sleep_time_usec - TIMER_ACCURACY_USEC)`
 */
int	ph_wait_until(struct timeval *endtvp)
{
	struct timeval	now;
	struct timeval	sub;
	unsigned int	sleep_time_usec;

	gettimeofday(&now, NULL);
	while (timercmp(&now, endtvp, < ))
	{
		timersub(endtvp, &now, &sub);
		if (sub.tv_sec >= 2)
			sleep_time_usec = 1000000 + TIMER_ACCURACY_USEC;
		else
			sleep_time_usec = sub.tv_sec * 1000000 + sub.tv_usec;
		if (sleep_time_usec > 1000000 + TIMER_ACCURACY_USEC)
			sleep_time_usec = 1000000;
		else if (sleep_time_usec > TIMER_ACCURACY_USEC)
			sleep_time_usec = sleep_time_usec - TIMER_ACCURACY_USEC;
		else
			sleep_time_usec = 0;
		if (usleep(sleep_time_usec) == -1)
			return (-1);
		gettimeofday(&now, NULL);
	}
	return (0);
}

struct timeval	ph_msectotimeval(unsigned int timesec)
{
	struct timeval	tv;

	tv.tv_sec = timesec / 1000;
	tv.tv_usec = (timesec % 1000) * 1000;
	return (tv);
}
