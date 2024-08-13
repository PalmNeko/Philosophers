/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:45:49 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/11 20:45:49 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_H
# define PH_H

#include <sys/time.h>
#include "ph_types.h"

int				ph_to_int(const char *str, int *num);
t_philosopher	*ph_new_philosopher(
					int time_to_die,
					int time_to_eat,
					int time_to_sleep,
					int must_eat_times);
void			ph_destroy_philosopher(t_philosopher *philo);
void			ph_error_print(const char *str);
int				ph_putstr(int fd, const char *str);
int				ph_main(int philo_cnt, t_manager *manager);
t_philosopher	*ph_clone_philosopher(t_philosopher *philo);
int				ph_logging(
					struct timeval *start_tvp, int no, t_philo_action action);
t_manager		*ph_new_manager(
					int time_to_die,
					int time_to_eat,
					int time_to_sleep,
					int must_eat_times);
void			ph_destroy_manager(t_manager *manager);
void			*ph_philo_routine(t_philosopher *philo);
void			ph_destroy_philosophers(t_philosopher *philos, int cnt);
int				ph_create_philo_threads(
					pthread_t *threads, t_philosopher *philos, int cnt);
void			*ph_philo_routine(t_philosopher *philo);

#endif
