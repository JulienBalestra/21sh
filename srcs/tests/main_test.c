#include <unistd.h>
#include "../../libft/includes/libft.h"
#include "../../includes/ast.h"
#include "../../includes/test.h"

int ast_testing(char *str, int debug)
{
	t_ast *ast;

	ft_putstr("\n\n [START] \"");
	ft_putstr(str);
	ft_putstr("\" [START] \n\n");
	if (debug)
		ft_putstr(" [ START ] ast_build [ START ]\n");
	ast = ast_build(ft_strdup(str));
	if (debug)
	{
		ft_putstr(" [ ENDED ] ast_build [ ENDED ]\n");
		ft_putstr("rrrrrrr [ START ] ast_read [ START ] rrrrrrr\n");
		ast_read(ast);
	}
	if (debug)
		ft_putstr("\nrrrrrrr [ END ] ast_read [ END ] rrrrrrr\n");
	ft_putstr("xxxxxxxx [ START ] ast_exec [ START ] xxxxxxxx\n");
	ast_exec(ast);
	ft_putstr("xxxxxxxx [ ENDED ] ast_exec [ ENDED ] xxxxxxxx\n\n");
	if (debug)
		ft_putstr(" [ START ] ast_clean [ START ]\n");
	ast_clean(ast);
	if (debug)
		ft_putstr(" [ ENDED ] ast_clean [ ENDED ]\n");
	ft_putstr(" [ENDED] \"");
	ft_putstr(str);
	ft_putstr("\" [ENDED]\n\n");
	return (0);
}

int ast_testing_main(void)
{
	int debug = 0;
	ft_putstr("----- [ START ] AST_TESTING [ START ] -----");

	ast_testing("/bin/echo simple", debug);
	ast_testing("/bin/ls -1r | /bin/cat -e | /usr/bin/sort | /usr/bin/rev | /usr/bin/rev", debug);
	ast_testing("/bin/ls -lr | /bin/cat -e > test_ls", debug);
	ast_testing("/bin/echo test_string | /bin/cat -e > test_echo", debug);
	ast_testing("/bin/echo test_string | /bin/cat -e >> test_echo", debug);
	ast_testing("/bin/cat -e < test_echo", debug);
	ast_testing("     /bin/cat      -e      <      test_echo", debug);
	ast_testing("/usr/bin/wc -w << hello", debug);

	ft_putstr("----- [ END ] AST_TESTING [ END ] -----\n\n");
	return (0);
}

int all(void)
{
	int ret;

	ret = 0;
	ret = ret + ast_testing_main();
	return (ret);
}

int main(int ac, char **av)
{
	int ret;

	ret = 0;
	if (ac == 1)
		all();
	else if (ac > 2)
	{
		ft_putstr_fd("too much args\n", 2);
		return (2);
	}
	else if (ft_strcmp(av[1], "all") == 0)
	{
		ret = all();
	}
	else if (ft_strcmp(av[1], "ast") == 0)
		ret = ast_testing_main();
	else
	{
		ft_putstr_fd("unknown args [", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd("]\n", 2);
		return (2);
	}

	ft_putstr("\nEnd of testing");
	ft_putstr("\nProcess id ");
	ft_putnbr(getpid());
	ft_putstr("\n");
	return (ret);
}