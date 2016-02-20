/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 16:27:24 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 16:27:26 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define READ      128
# define CWD       2048
# define DEFAULT_PS1 "21sh> "
# define DEFAULT_PS2 "> "
# define LEN_PS2 3
# define END_PROMPT "> "
# define USE_CWD	1

# define KEY_BACK        	127
# define KEY_DEL       		2117294875

# define KEY_RIGHT           4414235
# define KEY_LEFT            4479771

# define KEY_HOME            4738843
# define KEY_CTRL_A            1
# define KEY_END				4607771
# define KEY_CTRL_E            5

# define KEY_CTRL_LEFT		74995417045787
# define KEY_CTRL_RIGHT		73895905418011

# define KEY_CTRL_D				4

# define KEY_CTRL_U				21
# define KEY_CTRL_K				11
# define KEY_ALT_U				29979
# define KEY_ALT_K				27419

# define KEY_CTRL_Y				25
# define KEY_CTRL_UP			71696882162459
# define KEY_CTRL_DOWN			72796393790235

# include <string.h>
# include <term.h>

typedef struct		s_term
{
	long			c;
	int				cursor;
	struct s_term	*next;
	struct s_term	*prev;
}					t_term;

typedef struct		s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*name;
	char			*value;
}					t_env;

typedef struct		s_con
{
	int 			debug_fd;
	t_term			*yank;
	t_term			*undo;
	size_t			total_lines;
	size_t			line_position;
	size_t 			char_position;

}					t_con;

typedef struct		s_sh
{
	t_env			*env;
	struct s_sh		*mock;
	char			**l_env;
	char			*ps1;
	size_t			len_ps1;
	int				l_ret;
	char			**l_cmd;
	char			*buf;
	int				exit;
	struct termios	default_term;
	t_con			*console;
}					t_sh;

typedef struct		s_be
{
	int				ignore;
	int				unet;
	int				set;
	int				null;
	int				cmd;
}					t_be;

typedef struct      s_ast
{
	int 			op;
	int 			stdin;
	int 			stdout;
	int 			stderr;
	int 			from;
	int 			to;
	char 			**cmd;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

char				*triple_join(char *s1, char *s2, char *s3);
void				ft_remove_endchar(char *str, char c);
int					is_only_spaces(char *buf);
void		display_prompt(t_sh *shell, int ps2);
void				display_command_not_found(char *command);
int					make_exploitable(char **command, char **last_environ);
int					len_to_char(char *str, char c);
char				**override_last_environ(t_sh *shell);
char				**build_tab_environ(t_env *env);
void				clean_program(t_sh *shell);
int					start_exec(const char **str, t_sh *shell,
								char **mock_environ, int mock);
int					manage_builtins(char **command, t_sh *shell);
void				builtin_env(char **command, t_sh *shell);
void				builtin_unsetenv(char **command, t_sh *shell);
void				builtin_setenv(char **command, t_sh *shell);
void				manage_interpretor(char **command, t_sh *shell);
void				builtin_exit(char **command, t_sh *shell);
void				builtin_getenv(char **command, t_sh *shell);
char				*get_env_value(char *name, t_env *env);
void				builtin_cd(char **command, t_sh *shell);
void				ft_setenv(char *name, char *value, t_sh *shell);
void				convert_chars(char *str);
t_env				*create_env_link(t_env *env, char *environ_entry);
t_sh				*create_shell_from(char **environ_tab);
t_sh				*create_shell_props(void);
t_env				*manage_empty_environ(void);
int					is_ignore_arg(char *arg);
int					is_null_arg(char *arg);
int					have_unsets(char **command);
int					is_only_env(char **command);
int					have_null(char **command);
int					have_ignore(char **command);
int					have_setenv(char **command);
int					is_setenv(char *arg);
int					have_command(char **command);
int					is_benv_errors(t_be *benv);
void				display_environ(char **to_display, int end_line);
void				display_only_setenv(char **command, int end_line);
int					is_benv_do_nothing(t_be *benv);
void				run_under_new_environ(char **command, t_sh *shell);
t_env				*get_start(t_env *env);
void				delete_list(t_env **env);
void				display_not_such(char *who, char *where);
char				**get_mock_environ(char **command);
t_env				*upsert_link(t_env *env, char *environ_entry);
void				run_under_alter_environ(char **command,
											t_sh *shell);
char				**merge_both_environ(char **first,
									char **unset, char **second);
void				destroy_env_link(t_env *env);
size_t				len_env(t_env *env);
t_env				*get_end(t_env *env);
void				alter_environ_and_display(char **command,
											t_sh *shell, int end_lines);
int					is_d_var(char *variable);
char				*transform_dollar_builtin(char *entry, t_sh *shell);
int					is_dollar_builtin(char *entry);
char				*replace_dollar_dollar(char *dollar_question);
char				*replace_dollar_question(char *dollar_question,
												t_sh *shell);
int					is_real_line(char *buf);
t_ast				**build_command(t_sh *shell);
char				*get_line(t_sh *shell, int ps2);
int					existing_line(t_sh *shell);
void				go_to_old_pwd(t_sh *shell, int p);
void				go_to_home_directory(t_sh *shell);
void				change_dir(char *path, t_sh *shell, int p);
int					is_enter(char *buf);
int					cust_atoi(const char *nptr);
int					correct_syntax(t_sh *shell);
void				display_permission_denied(const char *command);
int					is_goto_home(char **command);
void				ensure_pwd(t_sh *shell);
char				*remove_duplicate_slash(char *path);
void				display_is_directory(const char *command);
void				transform_tilde(char **command, t_sh *shell);
int					is_tilde_transform(char *str, char c);
char				*troncate_dots(char *path);
int					is_logical_goto_oldpwd(char **str);
int					is_physical_goto_oldpwd(char **str);
int					is_legal_options(char **str, t_sh *shell);
void				display_cd_invalid_option(char *opt);
int					is_physical(char *str);
int					is_logical(char *str);
int					is_minus(char *str);
char				*create_cwd(t_sh *shell);
char				*create_chdir_path(char *path, t_sh *shell);
void				display_cd_permission(char *path);
void				cd_symblink(char *path, t_sh *shell);

t_ast				*ast_build(char *input, int eof, t_sh *shell);
void                ast_clean(t_ast *ast);
int                 ast_exec(t_ast *ast, t_sh *shell);
void                exec_with_recurse(t_ast *ast, t_sh *shell);
void                manage_simple_read(t_ast *ast, t_sh *shell);
void                manage_write(t_ast *ast, t_sh *shell);
void                manage_pipe(t_ast *ast, t_sh *shell);
void                manage_double_read(t_ast *ast, t_sh *shell);
void                ast_read(t_ast *ast);

int					next_char_is(char *str, char c);

int 				syn_semi_col(char *str);
int syn_right(char *str);
int syn_pipe(char *str);
int syn_left(char *str);
char *get_eof(char *s);
char *build_eof_entry(char *eof, t_sh *shell);
int skip_eof(char *s);

t_ast		*ast_printf_with_eof(char *input);
char **build_eof_tab(char *entry);
char		**cut_input(char *input, int *tuple);
void trigger_operator_with_recurse(t_ast *ast, char *input, int *tuple, t_sh *shell);
void trigger_command(t_ast *ast, char *input, int eof);

void change_fd(t_ast *ast);

/*
 * tc_init.c
 */
void raw_terminal_mode(t_sh *shell);
void 	default_terminal_mode(t_sh *shell);

size_t		len_prompt(t_sh *shell);
int 	tc_continue_process_key(t_sh *shell, t_term *term, long key);
t_term *create_link(void);
void safe_free_term(t_term *term);
void 	display_term_line(t_sh *shell, t_term *term);
int get_total_len(t_term *term);
t_term *get_current_cursor(t_term *term);
size_t			get_columns(void);

/*
 * tc_.move_home_end.c
 */
void exec_move_cursor_home(t_sh *shell, t_term *term);
void exec_move_cursor_end(t_sh *shell, t_term *term);

/*
 * tc_move_words.c
 */
void exec_move_cursor_left_word(t_sh *shell, t_term *term);
void exec_move_cursor_right_word(t_sh *shell, t_term *term);

/*
 * tc_move_letter.c
 */
void exec_move_cursor_right(t_sh *shell, t_term *term);
void exec_move_cursor_left(t_sh *shell, t_term *term);

/*
 * tc_remove_letter.c
 */
void exec_del_right(t_sh *shell, t_term *term);
void exec_del_and_move_left(t_sh *shell, t_term *term);

/*
 * tc_cut_line.c
 */
void exec_cut_line_left(t_sh *shell, t_term *term);
void exec_cut_line_right(t_sh *shell, t_term *term);

/*
 * tc_actions.c
 */
int		tc_action_keys(t_sh *shell, t_term *term, long key);
void	ft_putlong_fd(long n, int fd);

/*
 * tc_keys_misc.c
 */
void	insert_link_before(t_term *term);

/*
 * tc_yank.c
 */
void	insert_yank(t_sh *shell, t_term *term);

/*
 * tc_last.c
 */
void term_dup(t_sh *shell, t_term *term);
void restore_last(t_sh *shell, t_term *term);

/*
 * tc_debug.c
 */
# define DEBUG_FD        shell->console->debug_fd
# define CONSOLE	shell->console
int create_debug_file(void);

void 	erase_line(size_t len);
void 		update_ps1(t_sh *shell);

/*
 * ast_build_fn3.c
 */
void mock_ps1_by_ps2(t_sh *shell);
char *join_free_start(char *start, char *end);
int skip_eof(char *s);


/*
 * tc_move_up_down.c
 */
void exec_move_cursor_upline(t_sh *shell, t_term *term);
void exec_move_cursor_downline(t_sh *shell, t_term *term);

/*
 * tc_copy_line.c
 */
void term_dup_left(t_sh *shell, t_term *term);
void term_dup_right(t_sh *shell, t_term *term);

#endif
