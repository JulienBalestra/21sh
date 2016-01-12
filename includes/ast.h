//
// Created by jynlee on 12/01/16.
//

#ifndef INC_21SH_AST_H
#define INC_21SH_AST_H

typedef struct	s_ast
{
	int 			op;
	int 			stdin;
	int 			stdout;
	char 			**cmd;
	struct s_ast	*left;
	struct s_ast	*right;

}					t_ast;

t_ast *build_ast(char *input);
void clean_ast(t_ast *ast);
int ast_exec(t_ast *ast);
void exec_with_recurse(t_ast *ast);

void manage_simple_read(t_ast *ast);
void manage_write(t_ast *ast);
void manage_pipe(t_ast *ast);
void manage_double_read(t_ast *ast);

#endif //INC_21SH_AST_H
