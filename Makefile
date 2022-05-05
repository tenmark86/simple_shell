OBJDIR = targets/
CFLAGS = -Wall -Wextra -Werror -pedantic -g
OBJ = $(addprefix $(OBJDIR), $(patsubst %.c, %.o, $(wildcard *.c)))
CFILES = $(wildcard *.c)
TESTDIR = test_cases/checker/
TESTS = env exit

hsh: $(OBJDIR) $(OBJ)

	gcc $(CFLAGS) -o hsh $(OBJ)

$(OBJDIR)%.o: %.c headersh.h
	gcc $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR);

.PHONY: all
all : hsh


.PHONY: clean
clean:
	@rm -rf $(OBJDIR)
