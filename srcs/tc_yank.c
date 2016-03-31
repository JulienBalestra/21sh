/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_yank.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 14:53:08 by jubalest          #+#    #+#             */
/*   Updated: 2016/03/31 14:53:09 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	insert_yank(t_sh *shell, t_term *term)
{
	t_term *yank;

	yank = shell->yank;
	while (term->cursor == 0)
		term = term->prev;
	while (yank->prev)
		yank = yank->prev;
	while (yank)
	{
		insert_link_before(term);
		term->prev->c = yank->c;
		display_term_line(shell, term);
		yank = yank->next;
	}
}
