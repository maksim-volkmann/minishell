/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:48:08 by mvolkman          #+#    #+#             */
/*   Updated: 2024/03/14 11:57:18 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_isalpha(int c)
{
	return (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')));
}
