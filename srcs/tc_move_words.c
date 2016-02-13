#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void exec_move_cursor_left_word(t_sh *shell, t_term *term)
{
	(void)shell;
	int i;

	term = get_current_cursor(term);
	i = (term->c == ' ' || term->c == '\n');
	while (term->prev)
	{
		term->cursor = 0;
		term->prev->cursor = 1;
		ft_putstr(tgetstr("le", NULL));
		term = term->prev;
		if (! term)
			break;
		if (i == 0 && term->c == ' ')
			break;
		else if (i == 1 && term->c != ' ')
			i = 0;
	}
}

void exec_move_cursor_right_word(t_sh *shell, t_term *term)
{
	(void)shell;
	int i;

	term = get_current_cursor(term);
	i = (term->c == ' ' || term->c == '\n');
	while (term->next)
	{
		term->cursor = 0;
		term->next->cursor = 1;
		ft_putstr(tgetstr("nd", NULL));
		term = term->next;
		if (! term)
			break;
		if (i == 0 && term->c == ' ')
			break;
		else if (i == 1 && term->c != ' ')
			i = 0;
	}
}