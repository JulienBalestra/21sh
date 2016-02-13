#include "../includes/minishell.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

#define KEY_BACK        	127
#define KEY_DEL       		2117294875

#define KEY_RIGHT           4414235
#define KEY_LEFT            4479771

#define KEY_HOME            4738843
#define KEY_CTRL_A            1
#define KEY_END				4607771
#define KEY_CTRL_E            5

#define KEY_CTRL_LEFT		74995417045787
#define KEY_CTRL_RIGHT		73895905418011

#define KEY_CTRL_D				4

#define KEY_CTRL_U				21
#define KEY_CTRL_K				11


t_term *get_current_cursor(t_term *term)
{
	while (term->next)
		term = term->next;
	while (term->cursor == 0)
		term = term->prev;
	return (term);
}

void exec_move_cursor_right(t_sh *shell, t_term *term)
{
	(void)shell;
	term = get_current_cursor(term);
	if (term->next)
	{
		term->cursor = 0;
		term->next->cursor = 1;
		ft_putstr(tgetstr("nd", NULL));
	}
}

void exec_move_cursor_left(t_sh *shell, t_term *term)
{
	(void)shell;
	term = get_current_cursor(term);
	if (term->prev)
	{
		term->cursor = 0;
		term->prev->cursor = 1;
		ft_putstr(tgetstr("le", NULL));
	}
}

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

void exec_del_right(t_sh *shell, t_term *term)
{
	t_term	*next_link;

	(void)shell;
	term = get_current_cursor(term);
	if (term->next)
	{
		next_link = term->next;
		if (term->prev)
			term->prev->next = next_link;
		next_link->prev = term->prev;
		free(term);
		next_link->cursor = 1;
		ft_putstr(tgetstr("dc", NULL));
	}
}

void exec_del_and_move_left(t_sh *shell, t_term *term)
{
	t_term	*prev_link;

	(void)shell;
	term = get_current_cursor(term);
	if (term->prev)
	{
		prev_link = term->prev;
		if (prev_link->prev)
			prev_link->prev->next = term;
		term->prev = prev_link->prev;
		free(prev_link);
		ft_putstr(tgetstr("le", NULL));
		ft_putstr(tgetstr("dc", NULL));
	}
}

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

int	del_keys(t_sh *shell, t_term *term, long key)
{
	if (key == KEY_BACK)
		exec_del_and_move_left(shell, term);
	else if (key == KEY_DEL)
		exec_del_right(shell, term);
	else
		return (0);
	return (1);
}

int	cut_keys(t_sh *shell, t_term *term, long key)
{
	if (key == KEY_CTRL_U)
		exec_cut_line_left(shell, term);
	else if (key == KEY_CTRL_K)
		exec_cut_line_right(shell, term);
	else
		return (0);
	return (1);
}

int	move_keys(t_sh *shell, t_term *term, long key)
{
	if (key == KEY_LEFT)
		exec_move_cursor_left(shell, term);
	else if (key == KEY_RIGHT)
		exec_move_cursor_right(shell, term);
	else if (key == KEY_HOME || key == KEY_CTRL_A)
		exec_move_cursor_home(shell, term);
	else if (key == KEY_END || key == KEY_CTRL_E)
		exec_move_cursor_end(shell, term);
	else if (key == KEY_CTRL_LEFT)
		exec_move_cursor_left_word(shell, term);
	else if (key == KEY_CTRL_RIGHT)
		exec_move_cursor_right_word(shell, term);
	else
		return (0);
	return (1);
}

void	ft_putlong(long n)
{
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n > 9)
	{
		ft_putlong(n / 10);
		ft_putlong(n % 10);
	}
	else
		ft_putchar((char)(48 + n));
}

int  tc_action_keys(t_sh *shell, t_term *term, long key)
{
	//ft_putchar('*'); ft_putlong(key);ft_putchar('*'); // TODO DEBUG

	if (del_keys(shell, term, key))
		return (1);
	else if (move_keys(shell, term, key))
		return (2);
	else if (cut_keys(shell, term, key))
		return (3);
	else
		return (0);
}

void 	insert_link_before(t_term *term)
{
	t_term *link;

	link = create_link();
	if (link)
	{
		link->next = term;
		if (term->prev)
		{
			link->prev = term->prev;
			term->prev->next = link;
		}
		term->prev = link;
	}
}

void 	clear_line(int left, int len)
{
	char *le;
	char *dc;

	while(left)
	{
		le = tgetstr("le", NULL);
		if (! le )
		{
			return;
		}
		ft_putstr_fd(le, 1);
		left--;
	}
	while(len)
	{
		dc = tgetstr("dc", NULL);
		if (! dc)
		{
			return;
		}
		ft_putstr_fd(dc, 1);
		len--;
	}
}

int get_left_len(t_term *term)
{
	int len;

	len = 0;
	while(term->prev)
	{
		term = term->prev;
	}
	while (term->cursor == 0)
	{
		term = term->next;
		len++;
	}
	return (len);
}

int get_total_len(t_term *term)
{
	int len;

	len = 0;
	while(term->next)
	{
		term = term->next;
	}
	while (term->prev)
	{
		term = term->prev;
		len++;
	}
	return (len);
}

/*
 *  Erase all characters from CLI (based on len(term) - 1)
 *  and redisplay all char in term (after prompt that hasn't been erased)
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
	return (1);
}
