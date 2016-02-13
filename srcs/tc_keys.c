#include "../includes/minishell.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

/*
 *  Erase all characters from CLI (based on len(term) - 1)
 *  and redisplay all char in term (after prompt that hasn't been erased)
 *  term should point to cursor == 1
 */
void 	display_term_line(t_sh *shell, t_term *term)
{
	int left;
	int len;

	(void)shell;
	left = get_left_len(term);
	len = get_total_len(term);
	clear_line(left - 1, len);
	while (term->prev)
		term = term->prev;
	while (term->next)
	{
		ft_putchar((char)term->c);
		term = term->next;
	}
	while (term->cursor == 0)
	{
		ft_putstr(tgetstr("le", NULL));
		term = term->prev;
	}
}

int 	end_of_transmission(t_sh *shell, t_term *term)
{
	char *exit;
	char *ptr;

	while (term->next)
		term = term->next;
	if (term->prev)
		return (1);
	exit = ft_strdup("exit");
	ptr = exit;
	while (*exit)
	{
		tc_continue_process_key(shell, term, (long)*exit);
		exit++;
	}
	ft_strdel(&ptr);
	return (0);
}

int 	tc_continue_process_key(t_sh *shell, t_term *term, long key)
{
	(void)shell;
	if (key == '\n' || (char)key == '\n')
		return (0);
	else if (tc_action_keys(shell, term, key) == 0 && ft_isprint((char)key))
	{
		while (term->cursor == 0)
			term = term->prev;
		insert_link_before(term);
		term->prev->c = key;
		display_term_line(shell, term);
	}
	else if (key == KEY_CTRL_D)
	{
		return (end_of_transmission(shell, term));
	}
	term_dup(shell, term);
	return (1);
}
