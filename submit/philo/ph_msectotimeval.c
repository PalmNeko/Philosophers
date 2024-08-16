/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_msectotimeval.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 20:10:13 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/15 20:10:13 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

struct timeval	ph_msectotimeval(unsigned int timesec)
{
	struct timeval	tv;

	tv.tv_sec = timesec / 1000;
	tv.tv_usec = (timesec % 1000) * 1000;
	return (tv);
}
