/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_clone_philosopher.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:20:56 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/14 17:12:03 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <stdlib.h>

t_philosopher	*ph_clone_philosopher(t_philosopher *philo)
{
	t_philosopher	*cloned;

	(void)philo;
	cloned = ph_new_philosopher();
	return (cloned);
}
