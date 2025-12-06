NAME        = libcore.a
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -pipe
INCDIR      = includes
TMP_DIR     = tmp

# ============================================================================ #
#                               SOURCE MODULES                                 #
# ============================================================================ #

# 1. CORE SOURCE
CORE_DIR    = srcs/core
SRC_CORE    = $(shell find $(CORE_DIR) -name '*.c')
OBJ_CORE    = $(patsubst %.c, $(TMP_DIR)/%.o, $(SRC_CORE))

# 2. LIST SOURCE
LIST_DIR    = srcs/list
SRC_LIST    = $(shell find $(LIST_DIR) -name '*.c')
OBJ_LIST    = $(patsubst %.c, $(TMP_DIR)/%.o, $(SRC_LIST))

# 3. ALL SOURCE OBJECTS
OBJ_ALL     = $(OBJ_CORE) $(OBJ_LIST)

# ============================================================================ #
#                                TEST MODULES                                  #
# ============================================================================ #

# 1. CORE TESTS
TEST_DIR_CORE  = tests/core
TEST_SRC_CORE  = $(shell find $(TEST_DIR_CORE) -name '*.c')
TEST_BIN_CORE  = $(patsubst %.c, $(TMP_DIR)/%.test, $(TEST_SRC_CORE))

# 2. LIST TESTS
TEST_DIR_LIST  = tests/list
TEST_SRC_LIST  = $(shell find $(TEST_DIR_LIST) -name '*.c')
TEST_BIN_LIST  = $(patsubst %.c, $(TMP_DIR)/%.test, $(TEST_SRC_LIST))

# 3. ALL TEST BINARIES
TEST_BIN_ALL   = $(TEST_BIN_CORE) $(TEST_BIN_LIST)

# ============================================================================ #
#                                BUILD RULES                                   #
# ============================================================================ #

# Default target: Builds CORE only
core: $(OBJ_CORE)
	ar rcs $(NAME) $(OBJ_CORE)
	@echo "Core (Core) compiled."

# Ensure the library file target maps to core
$(NAME): core

# Target: Builds CORE + LIST
list: $(OBJ_CORE) $(OBJ_LIST)
	ar rcs $(NAME) $(OBJ_CORE) $(OBJ_LIST)
	@echo "Core (Core + List) compiled."

# Target: Builds ALL Modules
all: $(OBJ_ALL)
	ar rcs $(NAME) $(OBJ_ALL)
	@echo "Core (All Modules) compiled."

# Generic rule to compile .c to .o in TMP_DIR
$(TMP_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@

# ============================================================================ #
#                                TEST RULES                                    #
# ============================================================================ #

# Prevent make from deleting test objects
.SECONDARY: $(patsubst %.c, $(TMP_DIR)/%.o, $(TEST_SRC_CORE)) $(patsubst %.c, $(TMP_DIR)/%.o, $(TEST_SRC_LIST))

# --- Test Runner Macro ---
# Usage: $(call run_tests, <list_of_binaries>, <title_for_log>)
define run_tests
	@echo "Running $(2)..."
	@echo "Test Log ($(2)) - $$(date)" > tests_log
	@echo "----------------" >> tests_log
	@for test in $(1); do \
		echo "Running $$test" >> tests_log; \
		./$$test 2>&1 | perl -pe 's/\x1b\[[0-9;]*m//g' >> tests_log; \
		echo "----------------" >> tests_log; \
	done
	@echo "Done. Output saved to tests_log."
endef

# 1. Tests for CORE only (Default 'make tests')
test: core $(TEST_BIN_CORE)
	$(call run_tests, $(TEST_BIN_CORE), Core Tests)

# Aliases for core tests
test: tests
test_core: tests

# 2. Tests for CORE + LIST
test_list: list $(TEST_BIN_CORE) $(TEST_BIN_LIST)
	$(call run_tests, $(TEST_BIN_CORE) $(TEST_BIN_LIST), Core + List Tests)

# 3. Tests for EVERYTHING
test_all: all $(TEST_BIN_ALL)
	$(call run_tests, $(TEST_BIN_ALL), All Tests)

# Rule to link test executables in TMP_DIR
# Note: This depends on the corresponding .o file in TMP_DIR, which is built by the generic logic
$(TMP_DIR)/%.test: $(TMP_DIR)/%.o
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -L. -lcore -o $@

# ============================================================================ #
#                                  CLEANUP                                     #
# ============================================================================ #

clean:
	rm -rf $(TMP_DIR)
	rm -f tests_log

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re list tests tests_list tests_all core test test_core