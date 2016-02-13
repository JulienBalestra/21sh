#include "../includes/minishell.h"
#include "../libft/includes/libft.h"


void erase_cut_chars_left(t_term *yank)
{
	int len_y;

	len_y = get_total_len(yank);
	while (len_y >= 0)
	{
		ft_putstr(tgetstr("le", NULL));
		ft_putstr(tgetstr("dc", NULL));
		len_y--;
	}
}

void exec_cut_line_left(t_sh *shell, t_term *term)
{
	term = get_current_cursor(term);
	if (term->prev)
	{
		safe_free_term(shell->yank);
		shell->yank = term->prev;
		shell->yank->next = NULL;
		term->prev = NULL;
		erase_cut_chars_left(shell->yank);
	}
}

void erase_cut_chars_right(t_term *yank)
{
	int len_y;

	len_y = get_total_len(yank);
	while (len_y >= 0)
	{
		ft_putstr(tgetstr("dc", NULL));
		len_y--;
	}
}

void exec_cut_line_right(t_sh *shell, t_term *term)
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
		erase_cut_chars_right(shell->yank);
	}
}