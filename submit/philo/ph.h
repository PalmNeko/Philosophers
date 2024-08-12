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
int				ph_main(int philo_cnt, t_philosopher *template);
int				ph_logging(
					struct timeval *start_tvp, int no, t_philo_action action);

#endif
