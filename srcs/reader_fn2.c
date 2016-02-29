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

void	init_current_console(t_sh *shell, t_term *end, int ps2)
{
	erase_all_lines(shell);
	display_prompt(shell, ps2);
	raw_terminal_mode(shell);
	end->cursor = 1;
	end->c = '\n';
	CONSOLE->line_position = 1;
	CONSOLE->total_lines = 1;
}

void 	end_of_reading(t_sh *shell, int ps2, char *buf)
{
	erase_all_lines(shell);
	default_terminal_mode(shell);
	display_prompt(shell, ps2);
	ft_putstr_fd(buf, 1);
}

char	*recurse_get_line(t_sh *shell, int ps2, char *buf, t_term *end)
{
	ft_strdel(&buf);
	safe_free_term(end);
	return (get_line(shell, ps2));
}

char 	*end_of_file_recvd(t_sh *shell, char *buf, char *left, int limit)
{
	if (left)
		ft_strdel(&left);
	free(buf);
	if (shell)
		shell->close_program = 1;
	if (limit >= MAX_READ)
		ft_putstr_fd("ERROR max number of characters inside the buffer\n", 2);
	return (NULL);
}
