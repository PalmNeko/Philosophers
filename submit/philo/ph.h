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

# include <sys/time.h>
# include "ph_types.h"

int				ph_create_philo_threads(
					pthread_t *threads, t_philosopher *philos, int cnt);
int				ph_main(t_ph_config *manager);
int				ph_msleep_philo(unsigned int msec, t_philosopher *philo);
int				ph_print_log(struct timeval *start_tvp, t_log_info *info);
int				ph_putstr(int fd, const char *str);
int				ph_to_int(const char *str, int *num);
struct timeval	ph_msectotimeval(unsigned int timesec);
t_philosopher	*ph_generate_philosophers(t_manager *manager);
void			*ph_routine_observer(t_manager *manager);
void			*ph_routine_philo(t_philosopher *philo);
void			*ph_routine_philo(t_philosopher *philo);
void			*ph_routine_update_manager(t_manager *manager);
void			ph_destroy_philosophers(t_philosopher *philos, int cnt);
void			ph_print_action(t_philosopher *philo, t_philo_action action);
void			ph_print_error(const char *str);
void			ph_run_eat(t_philosopher *philo);
void			ph_run_sleep(t_philosopher *philo);
void			ph_run_think(t_philosopher *philo);
void			ph_set_end(t_manager *manager);
void			ph_wait_until_eatable(t_philosopher *philo);

#endif
