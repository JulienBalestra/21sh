/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 14:45:59 by jubalest          #+#    #+#             */
/*   Updated: 2016/03/31 14:46:01 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

void	display_term_characters(t_sh *shell, t_term *term)
{
	CONSOLE->total_lines = 1;
	while (term->next)
	{
		if (CONSOLE->char_position == get_columns())
		{
			ft_putchar('\n');
			erase_line(get_columns());
			CONSOLE->char_position = 0;
			CONSOLE->total_lines++;
			CONSOLE->line_position++;
		}
		ft_putchar((char)term->c);
		term = term->next;
		CONSOLE->char_position++;
	}
}

void	cursor_position(t_sh *shell, t_term *term)
{
	size_t	end;

	while (term->next)
		term = term->next;
	while (term->cursor == 0)
	{
		if (CONSOLE->char_position == 0 && term->prev)
		{
			ft_putstr(tgetstr("up", NULL));
			CONSOLE->line_position--;
			CONSOLE->char_position = get_columns() - 1;
			end = CONSOLE->char_position;
			while (end)
			{
				ft_putstr(tgetstr("nd", NULL));
				end--;
			}
			term = term->prev;
			continue;
		}
		ft_putstr(tgetstr("le", NULL));
		term = term->prev;
		CONSOLE->char_position--;
	}
}

void	display_term_line(t_sh *shell, t_term *term)
{
	erase_all_lines(shell);
	display_prompt(shell);
	while (term->prev)
		term = term->prev;
	CONSOLE->char_position = shell->len_ps1;
	display_term_characters(shell, term);
	cursor_position(shell, term);
}

int		end_of_transmission(t_sh *shell, t_term *term)
{
	while (term->next)
		term = term->next;
	if (term->prev)
		return (1);
	if (is_something_opened(shell->opened))
	{
		force_close_opened(shell->opened);
		shell->close_program = 1;
	}
	else if (shell->ddl_eof)
	{
		shell->close_program = 1;
		return (0);
	}
	play_exit(shell, term);
	return (0);
}

int		tc_continue_process_key(t_sh *shell, t_term *term, long key)
{
	if (key == '\n' || (char)key == '\n')
	{
		get_top_and_left(shell);
		safe_free_term(shell->current);
		shell->current = NULL;
		while (shell->hist && shell->hist->down)
			shell->hist = shell->hist->down;
		return (0);
	}
	else if (key == KEY_CTRL_D)
		return (end_of_transmission(shell, term));
	else if (tc_action_keys(shell, term, key) == 0 && ft_isprint((char)key))
	{
		while (term->cursor == 0)
			term = term->prev;
		insert_link_before(term);
		term->prev->c = key;
	}
	display_term_line(shell, term);
	return (1);
}
