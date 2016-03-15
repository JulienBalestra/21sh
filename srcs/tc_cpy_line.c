/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_cpy_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 11:42:38 by jubalest          #+#    #+#             */
/*   Updated: 2016/03/15 11:42:42 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	term_dup_left(t_sh *shell, t_term *term)
{
	t_term	*link;
	t_term	*prev;

	if (term == NULL)
		return ;
	safe_free_term(shell->yank);
	prev = NULL;
	link = NULL;
	term = get_current_cursor(term);
	term = term->prev;
	while (term)
	{
		link = create_term_link();
		if (prev)
		{
			link->next = prev;
			prev->prev = link;
		}
		link->c = term->c;
		link->cursor = term->cursor;
		term = term->prev;
		prev = link;
	}
	shell->yank = link;
}

void	term_dup_right(t_sh *shell, t_term *term)
{
	t_term	*link;
	t_term	*prev;

	if (term == NULL)
		return ;
	safe_free_term(shell->yank);
	prev = NULL;
	link = NULL;
	term = get_current_cursor(term);
	while (term->next)
	{
		link = create_term_link();
		if (prev)
		{
			link->prev = prev;
			prev->next = link;
		}
		link->c = term->c;
		link->cursor = term->cursor;
		term = term->next;
		prev = link;
	}
	shell->yank = link;
}
