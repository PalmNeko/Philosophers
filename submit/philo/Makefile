
NAME        = philo
FILE_PREFIX = ph
SRC         = \
	main.c \
	./ph_create_philo_threads.c \
	./ph_destroy_philosophers.c \
	./ph_generate_philosophers.c \
	./ph_main.c \
	./ph_msectotimeval.c \
	./ph_msleep_philo.c \
	./ph_print_action.c \
	./ph_print_error.c \
	./ph_print_log.c \
	./ph_putstr.c \
	./ph_routine_observer.c \
	./ph_routine_philo.c \
	./ph_routine_update_manager.c \
	./ph_run_eat.c \
	./ph_run_sleep.c \
	./ph_run_think.c \
	./ph_set_end.c \
	./ph_wait_until_eatable.c

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
