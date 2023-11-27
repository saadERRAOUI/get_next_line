NAME = get_next_line.a

CFLAGS = -Wall -Wextra -Werror

SOURCES = get_next_line.c get_next_line_utils.c

OBJECTS = $(SOURCES:.c=.o)

$(NAME): 
	gcc -c $(SOURCES)
	ar -rc $(NAME) $(OBJECTS)

all: $(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean 
	rm -f $(NAME)

re: fclean all
