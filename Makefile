
TARGET   = base64test
CC       = gcc


PREF_SRC = ./Src/
PREF_OBJ = ./Obj/

SRC      = $(wildcard $(PREF_SRC)*.c)
OBJ      = $(patsubst $(PREF_SRC)%.c, $(PREF_OBJ)%.o, $(SRC))

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)


$(PREF_OBJ)%.o : $(PREF_SRC)%.c
	$(CC) -c $< -o $@

clean     :
	rm $(TARGET) $(PREF_OBJ)*.o