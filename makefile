CC = gcc
CFLAGS = -Wall -I/usr/local/include
LDFLAGS = -L/usr/local/lib
LIBS = -lgsl -lgslcblas -lm

SRC = sample_cov_matrix.c
SRC_neon=NEON_sample_cov_matrix.c

OBJ = $(SRC:.c=.o)
OBJ_neon = $(SRC_neon:.c=.o)

TARGET = sample_cov_base
TARGET_ftree = sample_cov_ftree
TARGET_autovectorize_ftree = sample_cov_autovectorize_ftree
TARGET_neon = sample_cov_neon
TARGET_autovectorize_no_ftree = sample_cov_autovectorize_no_ftree

#---------------------------------------------------------------------------

non-neon: $(TARGET) $(TARGET_autovectorize_ftree) $(TARGET_ftree) $(TARGET_autovectorize_no_ftree)

all: $(TARGET) $(TARGET_neon) $(TARGET_autovectorize_ftree) $(TARGET_ftree) $(TARGET_autovectorize_no_ftree)

$(TARGET): $(OBJ)
	$(CC)  $(LDFLAGS) $^ $(LIBS) -o $@

$(TARGET_ftree): $(OBJ)
	$(CC) -ftree-vectorize $(LDFLAGS) $^ $(LIBS) -o $@

$(TARGET_autovectorize_ftree): $(OBJ)
	$(CC) -mfpu=neon -ftree-vectorize $(LDFLAGS) $^ $(LIBS) -o $@

$(TARGET_autovectorize_no_ftree): $(OBJ)
	$(CC) -mfpu=neon $(LDFLAGS) $^ $(LIBS) -o $@


$(TARGET_neon): $(OBJ2)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

#---------------------------------------------------------------------------

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_neon) $(TARGET) $(TARGET_neon)

run: $(TARGET)
	./$(TARGET)

run_neon: $(TARGET_neon)
	./$(TARGET_neon)
