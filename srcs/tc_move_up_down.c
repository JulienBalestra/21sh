#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void exec_move_cursor_upline(t_sh *shell, t_term *term)
{
	(void)shell;
	size_t term_len;

	term = get_current_cursor(term);
	term_len = get_columns();
	while (term->prev && term_len > 0)
	{
		term->cursor = 0;
		term->prev->cursor = 1;
		term = term->prev;
		term_len--;
	}
}
void exec_move_cursor_downline(t_sh *shell, t_term *term)
{
	(void)shell;
	size_t term_len;

	term = get_current_cursor(term);
	term_len = get_columns();
	while (term->next && term_len > 0)
	{
		term->cursor = 0;
		term->next->cursor = 1;
		term = term->next;
		term_len--;
	}
}