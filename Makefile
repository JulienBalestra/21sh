# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/20 11:34:39 by jubalest          #+#    #+#              #
#    Updated: 2015/03/11 12:50:57 by jubalest         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libsh
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
INC_DIR = includes/
SRC_DIR = srcs/
OBJ_DIR = .objects/
OBJS = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
TARGET = $(NAME).a
BIN = minishell
ENV = $(shell uname -s)


CL_CYAN = \033[0;36m
CL_GREED = \033[0;32m
CL_RED = \033[0;31m
CL_WHITE = \033[0m


SRC =               \
ast_build.c \
ast_build_fn.c \
ast_build_fn2.c \
ast_build_fn3.c \
ast_clean.c \
ast_exec.c \
ast_exec_fn.c \
ast_exec_fn2.c \
ast_read.c \
build_props.c \
builtin_cd.c \
builtin_env.c \
builtin_exit.c \
builtin_getenv.c \
builtin_setenv.c \
builtin_unsetenv.c \
cd_goto.c \
cd_is_valid.c \
cd_opt.c \
cd_symbolic.c \
chdir_var.c \
cleaner.c \
display_env.c \
empty_extern_environ.c \
env_errors.c \
format_path.c \
input_format.c \
main.c \
manage_builtins.c \
manage_exec.c \
manage_interpretor.c \
manage_link.c \
manage_path.c \
merge_environ.c \
misc_cd.c \
misc_cd2.c \
misc_interpretor.c \
misc_parse_env.c \
misc_prompt.c \
misc_prompt2.c \
misc_read.c \
misc_string.c \
parse_env.c \
reader.c \
run_under_env.c \
syntax.c \
syntax_fn.c \
syntax_token.c \
tc_actions.c \
tc_cut_line.c \
tc_init.c \
tc_keys.c \
tc_keys_misc.c \
tc_move_home_end.c \
tc_move_letter.c \
tc_move_words.c \
tc_remove_letter.c \
tc_yank.c \
tc_last.c \
tc_debug.c \
tc_move_up_down.c \
tc_cpy_line.c \
tc_history.c \
tc_term.c \
reader_fn1.c \
reader_fn2.c \
reader_fn3.c \
update_last_environ.c \
opened.c \
tc_opened.c \
tc_history_fn1.c


MAIN = srcs/main.c


.PHONY: all clean fclean re

default: all

all: $(NAME)
	@echo " # sh : Job done  $(shell pwd)/$(CL_GREED)$(TARGET)$(CL_WHITE)"
	@echo " # sh : Job done  $(shell pwd)/$(CL_GREED)$(BIN)$(CL_WHITE)"

$(NAME): $(OBJ_DIR) $(TARGET)

$(TARGET): $(OBJS)
	@make -C libft/ -j -s
	@echo " + sh : Creating  $(CL_GREED)$@$(CL_WHITE) $(shell sleep 0.01)"
	@ar -rcv $(TARGET) $(OBJS) > /dev/null
	@ranlib $(TARGET)
	@$(CC) $(CFLAGS) $(MAIN) $(TARGET) libft/libft.a -l termcap -I $(INC_DIR) -I libft/includes  -o $(BIN)

clean:
	@echo " $(shell\
				if [ -d $(OBJ_DIR) ];\
				then\
					echo "- sh : Removing $(CL_RED)$(OBJ_DIR)$(CL_WHITE) with$(CL_RED)";\
					ls $(OBJ_DIR) | wc -w; echo "$(CL_WHITE)*.o";\
					rm -Rf $(OBJ_DIR);\
				else\
					echo "# sh : Nothing to clean";\
				fi)"
	@make -C libft/ clean -s


fclean: clean
	@echo " $(shell\
					if [ -f libft/libft.a ];\
						then\
							echo "- ft : Removing  $(CL_RED)$ libft.a $(CL_WHITE)";\
							rm -f libft/libft.a;\
					else\
							echo "";\
					fi)"
	@echo " $(shell\
					if [ -f $(TARGET) ];\
					then\
						echo "- sh : Removing  $(CL_RED)$(TARGET)$(CL_WHITE)";\
						rm -f $(TARGET);\
					else\
						echo "# sh : Nothing to fclean";\
					fi)"
	@echo " $(shell\
					if [ -f $(BIN) ];\
						then\
							echo "- sh : Removing  $(CL_RED)$ $(BIN) $(CL_WHITE)";\
							rm -f $(BIN);\
					else\
							echo "# ft : Nothing to fclean";\
					fi)"
	@echo " $(shell\
					if [ -f $(TEST_BIN) ];\
						then\
							echo "- sh : Removing  $(CL_RED)$ $(TEST_BIN) $(CL_WHITE)";\
							rm -f $(TEST_BIN);\
					else\
							echo "# ft : Nothing to fclean";\
					fi)"

re: fclean all

$(addprefix $(OBJ_DIR), %.o): $(addprefix $(SRC_DIR), %.c)
	@echo " + sh : Compiling $(CL_CYAN)$(OBJ_DIR) < $^$(CL_WHITE)"
	@$(CC) $(CFLAGS) -I $(INC_DIR) -I libft/includes -o $@ -c $<

$(OBJ_DIR):
	@echo " # sh : $(ENV) kernel"
	@echo " + sh : Creating $(CL_GREED)$(OBJ_DIR)$(CL_WHITE)$(CL_WHITE)"
	@mkdir -p $(OBJ_DIR)