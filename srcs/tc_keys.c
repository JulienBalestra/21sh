#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

#define KEY_DEL				127
#define MYKEY_RIGHT			4414235
#define MYKEY_LEFT			4479771
#define MYKEY_UP			4283163
#define MYKEY_DO			4348699
#define MYKEY_ENTER			10 //437457162
#define MYKEY_HOME			4741915
#define MYKEY_END			4610843
#define MYKEY_SHFT_LE		74982532143899
#define MYKEY_SHFT_RI		73883020516123
#define MYKEY_SHFT_UP		71683997260571
#define MYKEY_SHFT_DO		72783508888347
#define MYKEY_SHFT_OPT_X	41932
#define MYKEY_SHFT_OPT_C	42956
#define MYKEY_SHFT_OPT_V	36044

#define ISMYKEY(x) (x == MYKEY_RIGHT || x == MYKEY_LEFT || x == KEY_DEL)

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

t_key   g_key_tab[] = {
    {MYKEY_RIGHT, exec_move_cursor_right},
	{MYKEY_LEFT, exec_move_cursor_left}
};

int  tc_exec_key(t_sh *shell, t_term *term, long key)
{
	int i;

	i = 0;
	while (i < 2)
	{
		if (key == g_key_tab[i].value)
		{
			g_key_tab[i].f(shell, term);
			return (1);
		}
		i++;
	}
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

int 	tc_process_key(t_sh *shell, t_term *term, long key)
{
	(void)shell;
	if (key == '\n' || (char)key == '\n')
		return (1);
	else if (tc_exec_key(shell, term, key) == 0)
	{
		while (term->cursor == 0)
			term = term->prev;

		insert_link_before(term);
		term->prev->c = key;
		display_term_line(shell, term);
	}
	return (0);
}
