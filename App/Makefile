CC = gcc
CFLAGS = -W -Wall
EXEC = DFA_DES
SRCDIR  = src
HEADDIR = head
OBJDIR  = bin


all: $(EXEC)
	
run: $(EXEC)
	./$(EXEC)


$(EXEC): $(OBJDIR)/DES_main.o $(OBJDIR)/DES_algo.o $(OBJDIR)/DES_atq.o
	$(CC) $^ -o $@


$(OBJDIR)/DES_main.o: $(HEADDIR)/DES_algo.h $(HEADDIR)/DES_atq.h


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS)


.PHONY: clean mrproper

clean:
	rm -rf *.o
	rm -rf $(OBJDIR)

mrproper: clean
	rm -rf $(EXEC)
