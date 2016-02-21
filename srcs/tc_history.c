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
			shell->hist = shell->hist->up;
		while (shell->hist->down)
		{
			char *buf = tterm_to_str(shell->hist->line);
			ft_putstr_fd(buf, shell->debug_fd);
			ft_strdel(&buf);
			ft_putstr_fd("\n", shell->debug_fd);
			shell->hist = shell->hist->down;
		}
		ft_putstr_fd("history_end\n", shell->debug_fd);
	//DEBUG
}

/*
 * term == \n and free all previous links
 * dup history links and linked with term \n
 */
void 	replace_body_from_tail(t_term *history, t_term *term)
{
	t_term *clean;
	t_term *tmp;

	while (history->next)
		history = history->next;
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
	history = history->prev;
	while (history)
	{
		tmp = create_term_link();
		tmp->c = history->c;
		term->prev = tmp;
		tmp->next = term;
		term = term->prev;
		history = history->prev;
	}
}

void 	exec_history_up(t_sh *shell, t_term *term)
{
	if (shell->hist)
	{
		term_dup_to_current(shell, term); // TODO

		if (shell->hist->up && compare_terms(shell->hist->up->line, term) && shell->hist->up->up)
			shell->hist = shell->hist->up; // TODO clean this

		replace_body_from_tail(shell->hist->line, term);
		if (shell->hist->up)
			shell->hist = shell->hist->up;
	}
}

void 	exec_history_down(t_sh *shell, t_term *term)
{
	if (shell->hist)
	{
		if (shell->hist->down)
		{
			if (compare_terms(shell->hist->down->line, term) && shell->hist->down->down)
				shell->hist = shell->hist->down;

			replace_body_from_tail(shell->hist->down->line, term);
			shell->hist = shell->hist->down;
		}
	}
}