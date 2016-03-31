/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_move_home_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 14:06:36 by jubalest          #+#    #+#             */
/*   Updated: 2016/03/31 14:06:38 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_move_cursor_home(t_sh *shell, t_term *term)
{
	(void)shell;
	term = get_current_cursor(term);
	while (term->prev)
	{
		term->cursor = 0;
		term->prev->cursor = 1;
		term = term->prev;
	}
}

void	exec_move_cursor_end(t_sh *shell, t_term *term)
{
	(void)shell;
	term = get_current_cursor(term);
	while (term->next)
	{
		term->cursor = 0;
		term->next->cursor = 1;
		term = term->next;
	}
}
