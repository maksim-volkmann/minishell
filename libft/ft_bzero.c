/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:14:40 by adrherna          #+#    #+#             */
/*   Updated: 2023/10/16 10:25:07 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*sus;
	size_t			i;

	i = 0;
	sus = s;
	while (i < n)
	{
		*sus = 0;
		sus++;
		i++;
	}
}

// int	main(void)
// {
// 	char str[] = "holaa";
// 	int i = 0;

// 	ft_bzero(str, sizeof(char) * 3);
// 	while (i < 5)
// 	{
// 		printf ("%c\n", str[i]);
// 		i++;
// 	}
// 	return (0);
// }
