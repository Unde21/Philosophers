NAME = philo_bonus

SRCS := srcs_bonus/main_bonus.c \
	srcs_bonus/parsing_bonus.c \
	srcs_bonus/ft_atoi_bonus.c \
	srcs_bonus/print_bonus.c \
	srcs_bonus/utils_bonus.c \
	srcs_bonus/init_bonus.c \
	srcs_bonus/init_child_bonus.c \
	srcs_bonus/routine_bonus.c \
	srcs_bonus/waiting_bonus.c \

	
HEADER := includes/philo_bonus.h
CC := cc
CFLAGS := -Wall -Wextra -Werror -g3
CPPFFLAGS := -MMD -MP

RM := rm -rf

SRC_DIR := srcs_bonus/
OBJ_DIR := .objs_bonus/
DEPS := $(OBJS:.o=.d)
INCS := -I./includes

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
BUILD := "🛠️"
SUCCESS := "🎉"
DONE := "🏁"

-include $(DEPS)

all: $(NAME)

$(NAME): $(OBJS) Makefile
	@$(CC) $(CFLAGS) $(OBJS) $(INCS) -o $@
	@echo "$(OK)$(MAGENTA)$(BOLD) Compilation successful !$(SUCCESS)$(END)"


$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@mkdir -p $(dir $@)
	@echo "$(BUILD)$(GREEN)$(BOLD) [Compiling...]$(END)"
	@$(CC) $(CFLAGS) $(INCS) $(CPPFFLAGS) -c -o $@ $<


$(OBJ_DIR):
	@mkdir -p $@

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(YELLOW)$(BOLD)$(CLEAN)Clean up...$(END)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(YELLOW)$(BOLD)$(CLEAN)Everything is clean !$(DONE)$(END)"

re: fclean all

.PHONY: all clean fclean re
