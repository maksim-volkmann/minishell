/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:43:46 by adrherna          #+#    #+#             */
/*   Updated: 2023/10/23 15:09:01 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nd_len;

	nd_len = ft_strlen(needle);
	if (*needle == 0)
		return ((char *)haystack);
	while (*haystack != 0 && len >= nd_len)
	{
		if (ft_strncmp(haystack, needle, nd_len) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}

// int	main(void)
// {
// 	const char	*str = "aaabcabcd";
// 	const char	*nd = "abcd";

// 	printf("%s\n", ft_strnstr(str, nd, -1));
// 	// printf("%s\n", strnstr(str, nd, -1));
// 	return (0);
// }
