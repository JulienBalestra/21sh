/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_cut_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 11:44:06 by jubalest          #+#    #+#             */
/*   Updated: 2016/03/15 11:44:09 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cut_line_left(t_sh *shell, t_term *term)
{
	term = get_current_cursor(term);
	if (term->prev)
	{
		safe_free_term(shell->yank);
		shell->yank = term->prev;
		shell->yank->next = NULL;
		term->prev = NULL;
	}
}

void	exec_cut_line_right(t_sh *shell, t_term *term)
{
	term = get_current_cursor(term);
	if (term->next && term->next->next)
	{
		safe_free_term(shell->yank);
		term->cursor = 0;
		shell->yank = term;
		while (term->next)
			term = term->next;
		term->prev->next = NULL;
		if (shell->yank->prev)
		{
			term->prev = shell->yank->prev;
			term->prev->next = term;
			shell->yank->prev = NULL;
		}
		else
			term->prev = NULL;
		term->cursor = 1;
	}
}
