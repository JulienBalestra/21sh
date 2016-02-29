/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:45:40 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:45:42 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

int 	is_print_buf(char *buf)
{
	int i;

	i = 0;
	while (i < READ)
	{
		if (! ft_isprint(buf[i]) && buf[i] != '\n')
		{
			ft_putstr_fd("ERROR not readable characters inside the buffer\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int 	process_signal(t_sh *shell, int catch_signal, t_term *end)
{
	if (catch_signal)
	{
		while (shell->console->total_lines > 1)
		{
			ft_putstr_fd("lines--", DEBUG_FD);
			ft_putchar_fd('\n', 1);
			shell->console->total_lines--;
		}
		nobody_from_tail(end);
	}
	return (0);
}