CC = gcc -O3
CFLAGS = -Wall -I/usr/local/include
LDFLAGS = -L/usr/local/lib
LIBS = -lgsl -lgslcblas -lm

SRC = sample_cov_matrix.c
SRC_neon=./neon/neon_test.c

OBJ = $(SRC:.c=.o)
OBJ_neon = $(SRC_neon:.c=.o)

TARGET = sample_cov_base
TARGET_ftree = sample_cov_ftree
TARGET_autovectorize_ftree = sample_cov_autovectorize_ftree
TARGET_neon = sample_cov_neon
TARGET_autovectorize_no_ftree = sample_cov_autovectorize_no_ftree
TARGET_blas_debug = sample_cov_debug

#---------------------------------------------------------------------------
debug: $(TARGET_blas_debug)

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


$(TARGET_neon): $(OBJ_neon)
	$(CC)  $(LDFLAGS) $^ $(LIBS) -lNE10 -mfpu=neon -o $@

$(TARGET_blas_debug): $(OBJ)
	gcc -g3 $(LDFLAGS) $^ $(LIBS) -o $@	
#---------------------------------------------------------------------------

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_neon) $(TARGET) $(TARGET_neon)

run: $(TARGET)
	./$(TARGET)

run_neon: $(TARGET_neon)
	./$(TARGET_neon)
