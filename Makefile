CFLAGS = -Wall -Wextra -Werror
CC = gcc
BINARY = client server
CFILES = server.c client.c
OBJECTS = $(CFILES:.c=.o)
FT_PRINTF = ft_printf/libftprintf.a 

all: $(BINARY)

client: client.o $(FT_PRINTF)
	$(CC) $(CFLAGS) $^ -o $@

server: server.o $(FT_PRINTF)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf client server

re: fclean all

.PHONY: all clean fclean re
