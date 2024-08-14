/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_logging.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:52:06 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/14 15:11:58 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include "ph_types.h"

int	ph_logging(struct timeval *start_tvp, t_log_info *info)
{
	char			*msg;
	struct timeval	diff;

	timersub(&info->tv, start_tvp, &diff);
	if (info->action == PH_PICK_UP)
		msg = "has taken a fork";
	if (info->action == PH_EAT)
		msg = "is eating";
	if (info->action == PH_SLEEP)
		msg = "is sleeping";
	if (info->action == PH_THINK)
		msg = "is thinking";
	if (info->action == PH_DIE)
		msg = "died";
	printf("%ld %d %s\n",
		diff.tv_sec * 1000 + diff.tv_usec / 1000, info->no, msg);
	return (0);
}
