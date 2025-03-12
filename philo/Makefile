NAME = philo

SRCS := srcs/main.c \
	srcs/ft_atoi.c \
	srcs/parsing.c \
	srcs/utils.c \
	srcs/init_threads.c \
	srcs/routine.c \
	srcs/check_status.c \
	srcs/waiting.c \
	

# SRCSB := 

HEADER := includes/philo.h

# HEADERB := includes/

CC := cc
CFLAGS := -Wall -Wextra -Werror
CPPFFLAGS := -MMD -MP

RM := rm -rf

SRC_DIR := srcs/
# SRCB_DIR := srcs_bonus/
OBJ_DIR := .objs/
# OBJB_DIR := .objs_bonus/
DEPS := $(OBJS:.o=.d)
# DEPSB := $(OBJSB:.o=.d)
INCS := -I./includes -I./libft

OBJS := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
# OBJSB := $(patsubst $(SRCB_DIR)%.c,$(OBJB_DIR)%.o,$(SRCSB))

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
# -include $(DEPSB)

all: $(NAME)

$(NAME): $(OBJS) Makefile
	$(CC) $(CFLAGS) $(OBJS) $(INCS) -o $@
	@echo "$(CYAN)$(BOLD)$(FIRE)$(NAME) made successfully!$(OK)$(END)"


$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCS) $(CPPFFLAGS) -c -o $@ $<

$(OBJ_DIR):
	@mkdir -p $@

# $(OBJB_DIR)%.o: $(SRCB_DIR)%.c $(HEADERB)
# 	@mkdir -p $(dir $@)
# 	@$(CC) $(CFLAGS) $(INCS) $(CPPFFLAGS) -c -o $@ $<

# bonus: .bonus

# .bonus: libft/libft.a $(OBJSB) Makefile
# 	$(CC) $(CFLAGS) $(OBJSB) $(INCS) ./libft/libft.a  -o $(NAME)
# 	@echo "$(MAGENTA)$(BOLD)$(FIRE)$(NAME) Bonus made successfully!$(OK)$(END)"
#.PHONY: bonus

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(YELLOW)$(BOLD)$(CLEAN)Objects directory cleaned$(CLEAN)$(END)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(YELLOW)$(BOLD)$(CLEAN)Everything cleaned $(DONE)$(END)"

re: fclean all

.PHONY: all clean fclean re
