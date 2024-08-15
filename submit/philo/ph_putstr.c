/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_puststr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:02:25 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/11 21:02:25 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ph_putstr(int fd, const char *str)
{
	int	size;

	size = 0;
	while (str[size] != '\0')
		size++;
	return (write(fd, str, size));
}
