CC = gcc
CFLAGS = -Wall -std=c11 -g
LDFLAGS = -lm

SRC = ejeep_route_manager.c helpers.c
TEST_DIR = tests
TEST_HELPERS = $(TEST_DIR)/test_helpers.c

TEST_NAMES = \
	test_add_stop_after \
	test_board_passengers \
	test_move_next \
	test_move_prev \
	test_remove_current_stop

TEST_RUNNERS = $(TEST_NAMES)

.PHONY: all run_tests clean

all: $(TEST_RUNNERS)

$(TEST_RUNNERS): % : $(TEST_DIR)/%.c $(SRC) $(TEST_HELPERS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

run_tests: all
	@for runner in $(TEST_RUNNERS); \
	do \
		./$$runner; \
	done

clean:
	rm -f $(TEST_RUNNERS) *.o