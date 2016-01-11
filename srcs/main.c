#include <unistd.h>
#include "../libft/includes/libft.h"
#include "../includes/ast.h"

int main(void)
{
	t_ast *ast;

	ft_putstr("\n---\n");
	char one[] = "/bin/ls -1r | /bin/cat -e | /usr/bin/sort | /usr/bin/rev | /usr/bin/rev";
	ast = build_ast(ft_strdup(one));
	ast_read(ast);
	ft_putstr("\n");
	if (ast_exec(ast))
	{
		//do_something;
	}
	clean_ast(ast);

	ft_putstr("\n---\n");
	char two[] = "/bin/ls -lr | /bin/cat -e > toto";
	ast = build_ast(ft_strdup(two));
	ast_read(ast);
	ft_putstr("\n");
	if (ast_exec(ast))
	{
		//do_something;
	}
	clean_ast(ast);

	ft_putstr("\n---\n");
	char three[] = "/bin/cat -e < toto";
	ast = build_ast(ft_strdup(three));
	ast_read(ast);
	ft_putstr("\n");
	if (ast_exec(ast))
	{
		//do_something;
	}
	clean_ast(ast);

	ft_putstr("\n---\n");
	char four[] = "/usr/bin/wc -w << hello";
	ast = build_ast(ft_strdup(four));
	ast_read(ast);
	ft_putstr("\n");
	if (ast_exec(ast))
	{
		//do_something;
	}
	clean_ast(ast);


	ft_putstr("\n\none_process: ");
	ft_putnbr(getpid());
	ft_putstr("\n");
	return (0);
}