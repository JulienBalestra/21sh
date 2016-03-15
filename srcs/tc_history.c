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

t_hist		*create_history(void)
{
	t_hist	*hist;

	if ((hist = (t_hist *)malloc(sizeof(t_hist))))
	{
		hist->down = NULL;
		hist->up = NULL;
		hist->line = NULL;
	}
	return (hist);
}

int 	compare_terms(t_term *one, t_term *two)
{
	char *str_one;
	char *str_two;
	int ret;

	str_one = tterm_to_str(one);
	str_two = tterm_to_str(two);
	ret = (ft_strcmp(str_one, str_two) == 0);
	ft_strdel(&str_one);
	ft_strdel(&str_two);
	return (ret);
}

void	add_to_history(t_sh *shell, t_term *term)
{
	t_hist *new_line;
	t_hist *browse;

	if (term->prev == NULL)
		return;
	if (shell->hist)
	{
		browse = shell->hist;
		while (browse->down)
			browse = browse->down;
		if (compare_terms(browse->line, term) == 0)
		{
			new_line = create_history();
			new_line->line = term;
			browse->down = new_line;
			new_line->up = browse;
		}
		else
			safe_free_term(term);
	}
	else
	{
		new_line = create_history();
		new_line->line = term;
		shell->hist = new_line;
	}
	//DEBUG
		ft_putstr_fd("history:\n", shell->debug_fd);
		while (shell->hist->up)
		{
			ft_putstr_fd("u-", shell->debug_fd);
			shell->hist = shell->hist->up;
		}
		while (shell->hist)
		{
			ft_putstr_fd("d-", shell->debug_fd);
			char *buf = tterm_to_str(shell->hist->line);
			ft_putstr_fd(buf, shell->debug_fd);
			ft_strdel(&buf);
			ft_putstr_fd("\n", shell->debug_fd);
			if (! shell->hist->down)
				break;
			shell->hist = shell->hist->down;
		}
		ft_putstr_fd("history_end\n", shell->debug_fd);
	//DEBUG
}

/*
 * term == \n and free all previous links
 * dup history links and linked with term \n
 */
void 	replace_body_from_tail(t_term *hist_term, t_term *term)
{
	t_term *clean;
	t_term *tmp;

	while (hist_term->next)
		hist_term = hist_term->next;
	while (term->next)
		term = term->next;
	if (term->prev)
	{
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
	term->cursor = 1;
	hist_term = hist_term->prev;
	while (hist_term)
	{
		tmp = create_term_link();
		tmp->c = hist_term->c;
		term->prev = tmp;
		tmp->next = term;
		term = term->prev;
		hist_term = hist_term->prev;
	}
}

void 	exec_history_up(t_sh *shell, t_term *term)
{
	if (shell->hist)
	{
		if (shell->hist->up && shell->current)
			shell->hist = shell->hist->up;
		term_dup_to_current(shell, term);
		replace_body_from_tail(shell->hist->line, term);
	}
}

void 	nobody_from_tail(t_term *term)
{
	t_term *tmp;
	t_term *clean;

	while (term->next)
		term = term->next;
	term->cursor = 1;
	clean = term->prev;
	term->prev = NULL;
	while (clean)
	{
		tmp = clean;
		clean = clean->prev;
		tmp->c = 0;
		tmp->cursor = 0;
		free(tmp);
	}
}

void 	exec_history_down(t_sh *shell, t_term *term)
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
		else if (shell->current && ! shell->current->prev)
		{
			nobody_from_tail(term);
		}
	}
}
