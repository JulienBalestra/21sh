#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void exec_move_cursor_home(t_sh *shell, t_term *term)
{
	(void)shell;

	term = get_current_cursor(term);
	while (term->prev)
	{
		term->cursor = 0;
		term->prev->cursor = 1;
		ft_putstr(tgetstr("le", NULL));
		term = term->prev;
	}
}

void exec_move_cursor_end(t_sh *shell, t_term *term)
{
	(void)shell;

	term = get_current_cursor(term);
	while (term->next)
	{
		term->cursor = 0;
		term->next->cursor = 1;
		ft_putstr(tgetstr("nd", NULL));
		term = term->next;
	}
}
