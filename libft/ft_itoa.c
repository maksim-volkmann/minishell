/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:26:37 by adrherna          #+#    #+#             */
/*   Updated: 2023/10/25 11:57:38 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digit_counter(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		count = 11;
		return (count);
	}
	if (n == 0)
	{
		count++;
		return (count);
	}
	if (n < 0)
	{
		n *= -1;
		count = 1;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*str;

	count = ft_digit_counter(n);
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *)malloc(count + 1 * sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		str[0] = '-';
	}
	str[count] = 0;
	while (n > 0)
	{
		str[--count] = (n % 10) + 48;
		n /= 10;
	}
	return (str);
}

// int	main(void)
// {
// 	char	*nb = ft_itoa(-2147483648);
// 	return (0);
// }
