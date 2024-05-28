/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:36:05 by adrherna          #+#    #+#             */
/*   Updated: 2024/05/28 08:40:08 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/_types/_null.h>

int main()
{
	const char *cmds[3][3] =
	{
		{"ls", "-l", NULL},
		{"cat", "file.txt", NULL},
		{"echo", "hello", "world", NULL}
	};
	return 0;
}