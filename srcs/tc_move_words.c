#include "../includes/minishell.h"

void	exec_move_cursor_left_word(t_sh *shell, t_term *term)
{
	int		i;

	(void)shell;
	term = get_current_cursor(term);
	i = (term->c == ' ' || term->c == '\n');
	while (term->prev)
	{
		term->cursor = 0;
		term->prev->cursor = 1;
		term = term->prev;
		if (! term)
			break;
		if (i == 0 && term->c == ' ')
			break;
		else if (i == 1 && term->c != ' ')
			i = 0;
	}
}

void	exec_move_cursor_right_word(t_sh *shell, t_term *term)
{
	int		i;

	(void)shell;
	term = get_current_cursor(term);
	i = (term->c == ' ' || term->c == '\n');
	while (term->next)
	{
		term->cursor = 0;
		term->next->cursor = 1;
		term = term->next;
		if (! term)
			break;
		if (i == 0 && term->c == ' ')
			break;
		else if (i == 1 && term->c != ' ')
			i = 0;
	}
}