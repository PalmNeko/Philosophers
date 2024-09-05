/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_set_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:34:53 by tookuyam          #+#    #+#             */
/*   Updated: 2024/09/05 17:34:53 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

void	ph_set_end(t_manager *manager)
{
	pthread_mutex_lock(&manager->lock);
	manager->in_process = false;
	pthread_mutex_unlock(&manager->lock);
}
