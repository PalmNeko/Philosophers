/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_msleep_acuracy_test.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 00:36:19 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/12 00:36:19 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// compile sample
// cc ph_msleep_accuracy_test.c "$(find .. -name "ph_msleep.c" | head)"

int	ph_msleep(unsigned int msec);

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	struct timeval	start;
	struct timeval	sub;
	struct timeval	cur;
	int				cnt;
	unsigned int	sleep_time;

	if (argc != 2)
		return (fprintf(stderr, "usage: %s [msleep]\n", argv[0]), 0);
	sleep_time = atoi(argv[1]);
	cnt = 0;
	gettimeofday(&start, NULL);
	while (cnt < 100)
	{
		ph_msleep(sleep_time);
		gettimeofday(&cur, NULL);
		timersub(&cur, &start, &sub);
		start = cur;
		printf("%d: %ld msec %ld usec  \n",
			cnt, sub.tv_sec * 1000 + sub.tv_usec / 1000, sub.tv_sec * 1000000 + sub.tv_usec);
		cnt++;
	}
	return (0);
}
