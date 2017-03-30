#
# Makfile for Quard Uart(ST16C554) example
#

CC= arm-linux-gcc

OBJS= main.o uart_api.o robot_protocol.o

EXEC= action_test

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -lpthread -o $@ $^

clean:
	rm -f $(OBJS) $(EXEC)
