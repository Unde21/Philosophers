NAME = philo

SRCS := srcs/main.c \
	srcs/parsing.c \
	srcs/ft_atoi.c \
	srcs/init.c \
	srcs/print.c \
	srcs/utils.c \
	srcs/create_threads.c \
	srcs/routine.c \
	srcs/action.c \
	srcs/check_status.c \
	srcs/waiting.c \
	
HEADER := includes/philo.h
CC := cc
CFLAGS := -Wall -Wextra -Werror -g3
CPPFFLAGS := -MMD -MP

RM := rm -rf

SRC_DIR := srcs/
OBJ_DIR := .objs/
DEPS := $(OBJS:.o=.d)
INCS := -I./includes -I./libft

OBJS := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

BOLD := \033[1m
GREEN := \033[0;32m
RED := \033[0;31m
BLUE := \033[0;34m
MAGENTA := \033[0;35m
CYAN    := \033[0;36m
YELLOW := \033[0;33m
END := \033[0m

CHECKMARK := "✔️"
WARNING := "⚠️"
FIRE := "🔥"
OK := "✅"
CLEAN := "🧹"
DONE := "🏁"

-include $(DEPS)

all: $(NAME)

$(NAME): $(OBJS) Makefile
	$(CC) $(CFLAGS) $(OBJS) $(INCS) -o $@
	@echo "$(CYAN)$(BOLD)$(FIRE)$(NAME) made successfully!$(OK)$(END)"


$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCS) $(CPPFFLAGS) -c -o $@ $<

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(YELLOW)$(BOLD)$(CLEAN)Objects directory cleaned$(CLEAN)$(END)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(YELLOW)$(BOLD)$(CLEAN)Everything cleaned $(DONE)$(END)"

re: fclean all

.PHONY: all clean fclean re
