CC = gcc
CFLAGS = -W -Wall
EXEC = DFA_DES
SRCDIR  = src
HEADDIR = head
OBJDIR  = bin


all: $(EXEC)
	
run: $(EXEC)
	./$(EXEC)


$(EXEC): $(OBJDIR)/DES_main.o $(OBJDIR)/DES_algo.o $(OBJDIR)/DES_atq.o $(OBJDIR)/DES_key_schedule.o $(OBJDIR)/DES_permutation.o
	$(CC) $^ -o $@


$(OBJDIR)/DES_main.o: $(HEADDIR)/DES_algo.h $(HEADDIR)/DES_atq.h
$(OBJDIR)/DES_algo.o: $(HEADDIR)/DES_key_schedule.h
$(OBJDIR)/DES_key_schedule.o: $(HEADDIR)/DES_permutation.h


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS)


.PHONY: clean mrproper

clean:
	rm -rf *.o
	rm -rf $(OBJDIR)

mrproper: clean
	rm -rf $(EXEC)
