NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft 

RM = rm -rf

SRCS = pipex.c utils.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@echo "Completed.."
	@$(MAKE) -C ./libft all --silent
	@$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME)

%.o: %.c 
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(MAKE) -C ./libft clean --silent
	@$(RM) $(OBJS)

fclean : clean
	@$(MAKE) -C ./libft fclean --silent
	@$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re