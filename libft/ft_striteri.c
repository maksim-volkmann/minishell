/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:37:28 by adrherna          #+#    #+#             */
/*   Updated: 2023/10/18 14:00:33 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_toupper(unsigned int index, char *c)
// {
// 	if (c[index] >= 'a' && c[index] <= 'z')
// 		c[index] -= 32;
// }

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] != 0)
	{
		f(i, &s[i]);
		i++;
	}
}
// int	main(void)
// {
// 	char hi[100] = "Hola mundo";

// 	printf("Before: %s\n", hi);
// 	ft_striteri(hi, ft_toupper);
// 	printf("After: %s\n", hi);
// }
