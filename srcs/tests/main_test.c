#include <unistd.h>
#include "../../libft/includes/libft.h"
#include "../../includes/ast.h"
#include "../../includes/test.h"

int ast_testing(char *str)
{
	t_ast *ast;

	ft_putstr("-> (0) ast_string [ START ]\n\n");
	ft_putstr(str);
	ft_putstr("\n\n-> (0) ast_string [ END ]\n\n");
	ft_putstr("-> (1) ast_build [ START ]\n\n");
	ast = ast_build(ft_strdup(str));
	ft_putstr("-> (1) ast_build [ END ]\n\n");
	ft_putstr("-> (2) ast_read [ START ]\n\n");
	ast_read(ast);
	ft_putstr("\n\n-> (2) ast_read [ END ]\n\n");
	ft_putstr("-> (3) ast_exec [ START ]\n\n");
	ast_exec(ast);
	ft_putstr("\n\n-> (3) ast_exec [ END ]\n\n");
	ft_putstr("-> (4) ast_clean [ START ]\n\n");
	ast_clean(ast);
	ft_putstr("-> (4) ast_clean [ END ]\n\n");
	return (0);
}

int ast_testing_main(void)
{
	ft_putstr("AST_TESTING [ START ]\n\n");

	//ast_testing("/bin/echo simple"); TODO
	ast_testing("/bin/ls -1r | /bin/cat -e | /usr/bin/sort | /usr/bin/rev | /usr/bin/rev");
	ast_testing("/bin/ls -lr | /bin/cat -e > test_ls");
	ast_testing("/bin/echo test_string | /bin/cat -e > test_echo");
	ast_testing("/bin/echo test_string | /bin/cat -e >> test_echo");
	ast_testing("/bin/cat -e < test_echo");
	ast_testing("     /bin/cat      -e      <      test_echo");
	ast_testing("/usr/bin/wc -w << hello");

	ft_putstr("AST_TESTING [ END ]\n\n");
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