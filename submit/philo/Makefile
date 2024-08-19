
NAME        = philo
FILE_PREFIX = ph
SRC         = \
	main.c \
	$(shell find . -name "$(FILE_PREFIX)_*.c")
OBJS        = $(SRC:.c=.o)
DEPS        = $(SRC:.c=.d)
CACHE_DIR   = cache
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -MMD -MP

all: $(NAME)

clean:
	rm -rf $(CACHE_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

test: norm

norm:
	! norminette *.c */*.c *.h | grep -v OK

debug: LDFLAGS += -g -O0 -fsanitize=leak
debug: CFLAGS  += -g -O0 -fsanitize=leak
debug: all

-include $(addprefix $(CACHE_DIR)/,$(DEPS))

$(NAME): $(addprefix $(CACHE_DIR)/,$(OBJS))
	$(CC) $(LDFLAGS) -o $@ $(filter %.o,$^) $(LDLIBS)

$(CACHE_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -MF $(CACHE_DIR)/$*.d -o $@ -c $<
