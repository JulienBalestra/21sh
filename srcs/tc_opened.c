#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

int 	is_something_opened(t_opened *open)
{
	if (open->double_quotes)
		return (1);
	else if (open->simple_quote)
		return (1);
	else if (open->back_quote)
		return (1);
	else if (open->parenthesis > 0)
		return (1);
	else if (open->braces > 0)
		return (1);
	else if (open->bracket > 0)
		return (1);
	return (0);
}

int 	revert_bool(int val)
{
	return (val ? 0 : 1);
}

void 	process_opened(t_opened *opn, char c)
{
	if (c == '"')
		opn->double_quotes = revert_bool(opn->double_quotes);
	else if (c == '\'')
		opn->simple_quote = revert_bool(opn->simple_quote);
	else if (c == '`')
		opn->back_quote = revert_bool(opn->back_quote);
	else if (c == '(')
		opn->parenthesis++;
	else if (c == ')')
		opn->parenthesis--;
	else if (c == '{')
		opn->braces++;
	else if (c == '}')
		opn->braces--;
	else if (c == '[')
		opn->bracket++;
	else if (c == ']')
		opn->bracket--;
}

void 	force_close_opened(t_opened *opened)
{
	opened->double_quotes = 0;
	opened->simple_quote = 0;
	opened->back_quote = 0;
	opened->parenthesis = 0;
	opened->braces = 0;
	opened->bracket = 0;
}