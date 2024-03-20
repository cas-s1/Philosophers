NAME := philo

CFLAGS := -Wall -Wextra -Werror -g

FILES := philo \

INCDIR := inc

SRCDIR := src

SRC := $(FILES:%=$(SRCDIR)/%.c)

OBJDIR := obj

OBJ := $(FILES:%=$(OBJDIR)/%.o)

$(NAME): $(OBJ)
	@cc $(CFLAGS) $(OBJ) -o $@

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@cc $(CFLAGS) $(INC) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
