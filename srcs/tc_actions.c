/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 14:32:15 by jubalest          #+#    #+#             */
/*   Updated: 2016/03/31 14:32:17 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

int		del_keys(t_sh *shell, t_term *term, long key)
{
	if (key == KEY_BACK)
		exec_del_and_move_left(shell, term);
	else if (key == KEY_DEL)
		exec_del_right(shell, term);
	else
		return (0);
	return (1);
}

int		cpycut_keys(t_sh *shell, t_term *term, long key)
{
	if (key == KEY_CTRL_U)
		exec_cut_line_left(shell, term);
	else if (key == KEY_CTRL_K)
		exec_cut_line_right(shell, term);
	else
		return (0);
	return (1);
}

int		last_yank_key(t_sh *shell, t_term *term, long key)
{
	char	*comp;

	if ((key == KEY_CTRL_MAJ_Y || key == KEY_CTRL_Y) && shell->yank)
		insert_yank(shell, term);
	else if (key == KEY_TAB)
	{
		comp = get_prev_chars(term);
		find_next(shell, term, comp);
		ft_strdel(&comp);
	}
	else
		return (0);
	return (1);
}

int		move_keys(t_sh *shell, t_term *term, long key)
{
	if (key == KEY_LEFT)
		exec_move_cursor_left(shell, term);
	else if (key == KEY_RIGHT)
		exec_move_cursor_right(shell, term);
	else if (key == KEY_HOME || key == KEY_CTRL_A || key == KEY_HOME_LINUX)
		exec_move_cursor_home(shell, term);
	else if (key == KEY_END || key == KEY_CTRL_E || key == KEY_END_LINUX)
		exec_move_cursor_end(shell, term);
	else if (key == KEY_MAJ_LEFT || key == KEY_CTRL_LEFT)
		exec_move_cursor_left_word(shell, term);
	else if (key == KEY_MAJ_RIGHT || key == KEY_CTRL_RIGHT)
		exec_move_cursor_right_word(shell, term);
	else if (key == KEY_MAJ_UP || key == KEY_CTRL_UP)
		exec_move_cursor_upline(shell, term);
	else if (key == KEY_MAJ_DOWN || key == KEY_CTRL_DOWN)
		exec_move_cursor_downline(shell, term);
	else if (key == KEY_UP)
		exec_history_up(shell, term);
	else if (key == KEY_DOWN)
		exec_history_down(shell, term);
	else
		return (0);
	return (1);
}

int		tc_action_keys(t_sh *shell, t_term *term, long key)
{
	if (del_keys(shell, term, key))
		return (1);
	else if (move_keys(shell, term, key))
		return (2);
	else if (cpycut_keys(shell, term, key))
		return (3);
	else if (last_yank_key(shell, term, key))
		return (4);
	else
		return (0);
}
