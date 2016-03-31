/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_move_up_down.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 14:50:44 by jubalest          #+#    #+#             */
/*   Updated: 2016/03/31 14:50:45 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_move_cursor_upline(t_sh *shell, t_term *term)
{
	size_t	term_len;

	(void)shell;
	term = get_current_cursor(term);
	term_len = get_columns();
	while (term->prev && term_len > 0)
	{
		term->cursor = 0;
		term->prev->cursor = 1;
		term = term->prev;
		term_len--;
	}
}

void	exec_move_cursor_downline(t_sh *shell, t_term *term)
{
	size_t	term_len;

	(void)shell;
	term = get_current_cursor(term);
	term_len = get_columns();
	while (term->next && term_len > 0)
	{
		term->cursor = 0;
		term->next->cursor = 1;
		term = term->next;
		term_len--;
	}
}
