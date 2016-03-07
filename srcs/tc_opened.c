#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

int 	is_something_opened(t_opened *open)
{
	if (open->double_quotes)
	{
		return (1);
	}
	else if (open->simple_quote)
	{
		return (1);
	}
	else if (open->parenthesis)
	{
		return (1);
	}
	else if (open->braces)
	{
		return (1);
	}
	else if (open->bracket)
	{
		return (1);
	}
	else if (open->back_quote)
	{
		return (1);
	}
	return (0);
}

void 	process_opened(t_opened *opn, char c)
{
	ft_putchar('.');
	if (c == '"')
		opn->double_quotes ? ((opn->double_quotes = 0)) : ((opn->double_quotes = 1));
	else if (c == '\'')
		opn->simple_quote ? ((opn->simple_quote = 0)) : ((opn->simple_quote = 1));
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
	else if (c == '`')
		opn->back_quote ? ((opn->back_quote = 0)) : ((opn->back_quote = 1));
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