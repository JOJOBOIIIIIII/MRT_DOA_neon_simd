CC = gcc
CFLAGS = -Wall -I/usr/local/include
LDFLAGS = -L/usr/local/lib
LIBS = -lgsl -lgslcblas -lm

SRC = sample_cov_matrix.c
SRC_neon=NEON_sample_cov_matrix.c

OBJ = $(SRC:.c=.o)
OBJ_neon = $(SRC:.c=.o)

TARGET = sample_cov 
TARGET_neon = sample_cov_neon

all: $(TARGET) $(TARGET_neon)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

$(TARGET_neon): $(OBJ2)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_neon) $(TARGET) $(TARGET_neon)

run: $(TARGET)
	./$(TARGET)
run_neon: $(TARGET_neon)
	./$(TARGET_neon)
