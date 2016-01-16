#include <unistd.h>
#include <stdlib.h>
#include "../../includes/ast.h"
#include "../../libft/includes/libft.h"

#include "libft.h"
#include "ast.h"

int ast_testing(char *str, int debug)
{
	t_ast *ast;

	if (debug)
		ft_putstr("[ast_build]");
	ast = ast_build(ft_strdup(str));
	if (debug)
	{
	    ft_putstr("[/ast_build]\n");
	    ft_putstr("[ast_read]");
		ast_read(ast);
		ft_putstr("[/ast_read]\n");
		ft_putstr("[ast_exec]");
	}
	ast_exec(ast);

	if (debug)
	{
	    ft_putstr("[/ast_exec]\n");
	    ft_putstr("[ast_clean]");
    }
	ast_clean(ast);
	if (debug)
	{
	    ft_putstr("[/ast_clean]\n");
	}
	return (0);
}

int main(int ac, char **av)
{
	int ret = 0;
	int debug = 0;

	if (ac == 1)
	    return (1);
	if (getenv("DEBUG21"))
		debug = 1;
    ret = ast_testing(av[1], debug);
	return (ret);
}