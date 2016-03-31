/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:56:39 by jubalest          #+#    #+#             */
/*   Updated: 2016/03/15 10:56:45 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void	exec_history_down(t_sh *shell, t_term *term)
{
	if (shell->hist)
	{
		if (shell->hist->down)
		{
			shell->hist = shell->hist->down;
			replace_body_from_tail(shell->hist->line, term);
		}
		else if (shell->current && shell->current->prev)
		{
			replace_body_from_tail(shell->current, term);
		}
		else if (shell->current && !shell->current->prev)
		{
			nobody_from_tail(term);
		}
	}
}

void	exec_history_up(t_sh *shell, t_term *term)
{
	if (shell->hist)
	{
		if (shell->hist->up && shell->current)
			shell->hist = shell->hist->up;
		term_dup_to_current(shell, term);
		replace_body_from_tail(shell->hist->line, term);
	}
}

int		compare_terms(t_term *one, t_term *two)
{
	char	*str_one;
	char	*str_two;
	int		ret;

	str_one = tterm_to_str(one);
	str_two = tterm_to_str(two);
	ret = (ft_strcmp(str_one, str_two) == 0);
	ft_strdel(&str_one);
	ft_strdel(&str_two);
	return (ret);
}

void	clean_current_line(t_term *term)
{
	t_term	*clean;
	t_term	*tmp;

	clean = term->prev;
	while (clean)
	{
		tmp = clean;
		clean = clean->prev;
		tmp->cursor = 0;
		tmp->c = 0;
		tmp->next = NULL;
		tmp->prev = NULL;
		free(tmp);
	}
}
