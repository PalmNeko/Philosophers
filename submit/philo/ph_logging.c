/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_logging.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:52:06 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/12 15:17:08 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include "ph_types.h"

int	ph_logging(struct timeval *start_tvp, int no, t_philo_action action)
{
	char			*msg;
	struct timeval	now;
	struct timeval	diff;

	gettimeofday(&now, NULL);
	timersub(&now, start_tvp, &diff);
	if (action == PH_PICK_UP)
		msg = "has taken a fork";
	if (action == PH_EAT)
		msg = "is eating";
	if (action == PH_SLEEP)
		msg = "is sleeping";
	if (action == PH_THINK)
		msg = "is thinking";
	if (action == PH_DIE)
		msg = "died";
	printf("%ld %d %s\n", diff.tv_sec * 1000 + diff.tv_usec / 1000, no, msg);
	return (0);
}
