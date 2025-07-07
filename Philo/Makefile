NAME = philosophers

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = 	philo.c\
		utils.c\
		routine.c\
		monitoring.c\
		parser.c\
		init.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "🔧 Linking objects into executable..."
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "✅ Build complete: ./$(NAME)"

clean:
	@echo "🧼 Cleaning object files..."
	rm -f $(OBJS)

fclean: clean
	@echo "🗑️ Removing executable..."
	rm -f $(NAME)

re: fclean all
