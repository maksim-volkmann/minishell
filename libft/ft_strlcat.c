/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:35:32 by adrherna          #+#    #+#             */
/*   Updated: 2023/10/21 15:35:47 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_src;
	size_t	len_dst;

	i = 0;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (*src == 0)
		return (ft_strlen(dst));
	if (len_dst >= dstsize)
		return (dstsize + len_src);
	while (src[i] != 0 && len_dst + i < dstsize - 1)
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = 0;
	return (len_dst + len_src);
}

// int	main(void)
// {
// 	char dest1[10] = "01234";
// 	char src1[] = "56789";
// 	strlcat(dest1, src1, 9);
// 	printf("%s\n", dest1);

// 	char dest2[15] = "";
// 	char src2[] = "";
// 	ft_strlcat(dest2, src2, 15);
// 	printf("%s\n", dest2);
// 	return (0);
// }

	// if (*src == 0 || len_dst >= dstsize)
	// 	return (dstsize + len_src);
