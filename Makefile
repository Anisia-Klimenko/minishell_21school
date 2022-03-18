NAME	=	minishell

CC		=	cc
#  CFLAGS	=	-fsanitize=address -fsanitize=undefined \
# 				-fno-omit-frame-pointer -g \
# 				-Wall -Wextra -Werror \
				# -O0 -MMD
CFLAGS		= -Wall -Wextra -Werror -g

OBJDIR	=	obj
SRCDIR	=	src
LIBDIR	=	$(SRCDIR)/libft

LIBFT	=	libft.a

HEADER	=	minishell.h

RL_INCLUDE  =   ~/.brew/opt/readline/include
RL_LIB      =   ~/.brew/opt/readline/lib

SRC		=	$(SRCDIR)/main.c	\
			$(SRCDIR)/gnl/get_next_line.c	\
			$(SRCDIR)/gnl/get_next_line_utils.c	\
			$(SRCDIR)/minishell.c	\
			$(SRCDIR)/parser.c	\
			$(SRCDIR)/dollar.c	\
			$(SRCDIR)/quotes.c	\
			$(SRCDIR)/get_cmd.c	\
			$(SRCDIR)/utils.c	\
			$(SRCDIR)/utils2.c	\
			$(SRCDIR)/utils3.c	\
			$(SRCDIR)/ft_cd.c	\
			$(SRCDIR)/ft_cd2.c	\
			$(SRCDIR)/ft_export.c	\
			$(SRCDIR)/ft_export2.c	\
			$(SRCDIR)/ft_unset.c	\
			$(SRCDIR)/ft_echo_pwd_env_exit.c	\
			$(SRCDIR)/cmd_f.c	\
			$(SRCDIR)/dict_f.c	\
			$(SRCDIR)/list_f.c	\
			$(SRCDIR)/binary.c	\
			$(SRCDIR)/redirect.c	\
			$(SRCDIR)/pipes.c	\
			$(SRCDIR)/pipes2.c

OBJ		=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

GRN 	=	\033[0;32m
RED 	=	\033[0;31m
YEL 	=	\033[1;33m
END 	=	\033[0m
TICK	=	\xE2\x9C\x94

.PHONY	:	all clean fclean re

all		:	$(NAME)

$(NAME)	:	$(OBJ)
		@make bonus -C $(LIBDIR)/
		@cp $(LIBDIR)/$(LIBFT) ./
		@$(CC) $(CFLAGS) -lreadline -L $(RL_LIB) -I $(RL_INCLUDE) $(OBJ) $(LIBFT) -o $(NAME)
		@echo "\n\t$(GRN) $(TICK) MINISHELL compiled!$(END)\n"

$(OBJDIR)/$(SRCDIR)/%.o: 	$(SRCDIR)/%.c $(HEADER) Makefile
		@$(CC) $(CFLAGS) -c $< -o $@ -I $(RL_INCLUDE)

$(OBJDIR)/$(SRCDIR)/gnl/%.o: 	$(SRCDIR)/gnl/%.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR) :
		@mkdir $@ $@/$(SRCDIR) $@/$(SRCDIR)/gnl

$(OBJ) : | $(OBJDIR)

clean:
		@rm -rf $(OBJDIR)
		@make fclean -C $(LIBDIR)/
		@echo "$(RED)clean ...$(END)"

fclean: clean
		@rm -f $(NAME)
		@echo "$(RED)fclean ...$(END)"
		@rm -f $(LIBFT)

re: 	fclean all
