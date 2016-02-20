#include <stdlib.h>
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

t_hist		*create_history(void)
{
	t_hist	*hist;

	if ((hist = (t_hist *)malloc(sizeof(t_hist))))
	{
		hist->down = NULL;
		hist->up = NULL;
		hist->line = NULL;
	}
	return (hist);
}

void	add_to_history(t_sh *shell, t_term *term)
{
	t_hist *new_line;
	t_hist *browse;

	if ((new_line = create_history()))
	{
		new_line->line = term;
		if (shell->hist)
		{
			browse = shell->hist;
			while (browse->down)
				browse = browse->down;
			browse->down = new_line;
			new_line->up = browse;
		}
		else
			shell->hist = new_line;
	}
	/*//DEBUG
		char *buf = tterm_to_str(shell->hist->line);
		ft_putstr_fd(buf, CONSOLE->debug_fd);
		ft_strdel(&buf);
	//DEBUG*/
}

/*void 	exec_history_up(t_sh *shell, t_term *term)
{

}*/