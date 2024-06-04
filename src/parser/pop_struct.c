/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrherna <adrianhdt.2001@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:51:31 by adrherna          #+#    #+#             */
/*   Updated: 2024/06/04 10:15:36 by adrherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	ft_pop_struct(t_command	*cmds, char ***tarray)
{
	t_command	*new;
	int			i;

	i = 0;
	while (tarray[i] != NULL)
	{
		new = ft_new_node(tarray[i]);
		add_or_init_node(&cmds, new);
	}
}
