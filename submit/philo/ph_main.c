/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:09:23 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/11 21:09:23 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

t_philosopher	*ph_generate_philosophers(t_manager *manager);
int				ph_launch(t_manager *manager, t_philosopher *philos);
int				ph_philo_start(t_manager *manager, t_philosopher *philos);
int				ph_init_manager(t_manager *manager, t_ph_config *config);
void			ph_finalize_manager(t_manager *manager);

int	ph_main(t_ph_config *config)
{
	t_manager		manager;
	int				error;

	if (ph_init_manager(&manager, config) != 0)
		return (1);
	error = ph_launch(&manager, manager.philos);
	ph_finalize_manager(&manager);
	return (error);
}

int	ph_init_manager(t_manager *manager, t_ph_config *config)
{
	t_philosopher	*philos;

	memset(manager, 0, sizeof(t_manager));
	pthread_mutex_init(&manager->lock, NULL);
	gettimeofday(&manager->start, NULL);
	manager->config = config;
	manager->in_process = true;
	philos = ph_generate_philosophers(manager);
	if (philos == NULL)
		return (ph_finalize_manager(manager), ENOMEM);
	manager->philos = philos;
	return (0);
}

void	ph_finalize_manager(t_manager *manager)
{
	pthread_mutex_destroy(&manager->lock);
	ph_destroy_philosophers(manager->philos, manager->config->philo_cnt);
}

int	ph_launch(t_manager *manager, t_philosopher *philos)
{
	pthread_t		update_thread;
	pthread_t		observer_tid;
	int				error;

	error = pthread_create(&update_thread, NULL,
			(void *(*)(void *))ph_routine_update_manager, manager);
	if (error != 0)
		return (error);
	error = pthread_create(&observer_tid, NULL,
			(void *(*)(void *))ph_routine_observer, manager);
	if (error != 0)
		return (ph_set_end(manager), pthread_join(update_thread, NULL), error);
	error = ph_philo_start(manager, philos);
	ph_set_end(manager);
	pthread_join(update_thread, NULL);
	pthread_join(observer_tid, NULL);
	return (error);
}

int	ph_philo_start(t_manager *manager, t_philosopher *philos)
{
	pthread_t		*threads;
	int				index;
	int				error;

	threads = (pthread_t *)malloc(sizeof(pthread_t)
			* manager->config->philo_cnt);
	if (threads == NULL)
		return (ENOMEM);
	error = ph_create_philo_threads(
			threads, philos, manager->config->philo_cnt);
	if (error != 0)
		ph_set_end(manager);
	index = 0;
	while (index < manager->config->philo_cnt)
		pthread_join(threads[index++], NULL);
	free(threads);
	return (0);
}
