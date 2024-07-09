##
## EPITECH PROJECT, 2024
## B-SYN-400-PAR-4-1-abstractVM-rafael.sapalo-esteves
## File description:
## Makefile
##

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
INCLUDES = -Iinclude
SRC_DIR = src
OBJ_DIR = obj
TARGET = abstractVM
TEST_TARGET = test_stack

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

TEST_SRCS = $(wildcard test/*.cpp)
TEST_OBJS = $(TEST_SRCS:%.cpp=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: test/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

$(TEST_TARGET): $(TEST_OBJS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(TEST_OBJS) $(OBJS) -o $(TEST_TARGET) -lcriterion

all: $(TARGET)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(TARGET) $(TEST_TARGET)

re: fclean all

test_run: $(TEST_TARGET)
	./$(TEST_TARGET)

.PHONY: all clean fclean re test_run