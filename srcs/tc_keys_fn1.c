/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_keys_fn1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 14:48:17 by jubalest          #+#    #+#             */
/*   Updated: 2016/03/31 14:48:18 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

void	erase_line(size_t len)
{
	char	*le;
	char	*dc;

	while (len)
	{
		le = tgetstr("le", NULL);
		dc = tgetstr("dc", NULL);
		if (!le || !dc)
			return ;
		ft_putstr_fd(le, 1);
		ft_putstr_fd(dc, 1);
		len--;
	}
}

void	erase_all_lines(t_sh *shell)
{
	while (CONSOLE->line_position < CONSOLE->total_lines)
	{
		ft_putstr(tgetstr("do", NULL));
		CONSOLE->line_position++;
	}
	while (CONSOLE->line_position > 1)
	{
		erase_line(get_columns());
		ft_putstr(tgetstr("up", NULL));
		CONSOLE->line_position--;
	}
	erase_line(CONSOLE->char_position);
}

void	get_top_and_left(t_sh *shell)
{
	char	*le;

	while (CONSOLE->char_position > 1)
	{
		le = tgetstr("le", NULL);
		if (!le)
		{
			ft_putstr_fd("Env not loaded\n", 2);
			exit(2);
		}
		ft_putstr(le);
		CONSOLE->char_position--;
	}
	while (CONSOLE->line_position > 1)
	{
		ft_putstr(tgetstr("up", NULL));
		CONSOLE->line_position--;
	}
}

void	play_exit(t_sh *shell, t_term *term)
{
	char	*ex;
	char	*ptr;

	ex = ft_strdup("exit");
	ptr = ex;
	while (*ex)
	{
		tc_continue_process_key(shell, term, (long)*ex);
		ex++;
	}
	ft_strdel(&ptr);
}
