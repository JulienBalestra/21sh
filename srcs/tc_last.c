/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_last.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 14:49:38 by jubalest          #+#    #+#             */
/*   Updated: 2016/03/31 14:49:39 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	term_dup_to_current(t_sh *shell, t_term *term)
{
	t_term	*link;
	t_term	*prev;

	if (term == NULL || shell->current)
		return ;
	while (term->next)
		term = term->next;
	prev = NULL;
	link = NULL;
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
	while (link && link->next)
		link = link->next;
	shell->current = link;
}
