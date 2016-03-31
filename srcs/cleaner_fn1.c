/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:42:02 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:42:03 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/minishell.h"

void	delete_hashmap(t_sh *shell)
{
	t_bin	*bin;

	while (shell->map && shell->map->prev)
	{
		shell->map = shell->map->prev;
	}
	while (shell->map)
	{
		free(shell->map->name);
		bin = shell->map;
		shell->map = shell->map->next;
		free(bin);
	}
}
