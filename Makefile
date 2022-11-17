OBJS=CreateInput.o main.o 
cc=g++ -std=c++11
CFLAGS+=-c -Wall -g

main:$(OBJS)
	$(cc) $^ -o $@
%.o:%.c
	$(cc) $^ $(CFLAGS) -o $@
clean:
	$(RM) *.o main -r