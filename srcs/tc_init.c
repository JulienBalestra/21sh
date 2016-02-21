#include <term.h>
#include "../includes/minishell.h"
#include <stdlib.h>
#include <unistd.h>

void 	raw_terminal_mode(t_sh *shell)
{
	struct termios tattr;

	tcgetattr(STDIN_FILENO, &shell->default_termios);
	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ECHO | ICANON);
	tattr.c_oflag &= (OPOST);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &tattr);
	tgetent(NULL, getenv("TERM"));

	return;
}

void 	default_terminal_mode(t_sh *shell)
{
	tcsetattr(STDIN_FILENO, TCSADRAIN, &shell->default_termios);
}
