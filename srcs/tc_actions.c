#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

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

int last_yank_key(t_sh *shell, t_term *term, long key)
{
	if (key == KEY_CTRL_Y && CONSOLE->yank)
		insert_yank(shell, term);
	/*else if (key == KEY_CTRL__ && shell->last)
		restore_last(shell, term);*/
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

void	ft_putlong(long n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n > 9)
	{
		ft_putlong(n / 10, fd);
		ft_putlong(n % 10, fd);
	}
	else
		ft_putchar_fd((char)(48 + n), fd);
}

int  tc_action_keys(t_sh *shell, t_term *term, long key)
{
	//ft_putlong(key, D_FD); ft_putchar_fd('\n', D_FD); // TODO DEBUG

	if (del_keys(shell, term, key))
		return (1);
	else if (move_keys(shell, term, key))
		return (2);
	else if (cut_keys(shell, term, key))
		return (3);
	else if (last_yank_key(shell, term, key))
		return (4);
	else
		return (0);
}