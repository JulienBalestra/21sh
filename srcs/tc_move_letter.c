#include "../includes/minishell.h"

void	exec_move_cursor_right(t_sh *shell, t_term *term)
{
	(void)shell;
	term = get_current_cursor(term);
	if (term->next)
	{
		term->cursor = 0;
		term->next->cursor = 1;
	}
}

void	exec_move_cursor_left(t_sh *shell, t_term *term)
{
	(void)shell;
	term = get_current_cursor(term);
	if (term->prev)
	{
		term->cursor = 0;
		term->prev->cursor = 1;
	}
}
