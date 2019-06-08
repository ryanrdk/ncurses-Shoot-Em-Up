# Colour
C = \033[0;36m
R = \033[0;91m
P = \033[1;95m
G = \033[4;32m
E = \033[0m

# Name
PROG := run

FILES = main.cpp  Entity.cpp Player.cpp Enemy.cpp
SRC_DIR = src
SRCS = src/main.cpp  src/Entity.cpp src/Player.cpp src/Enemy.cpp
OBJDIR = obj
OBJS = obj/main.o  obj/Entity.o obj/Player.o obj/Enemy.o

# Sources
# SRCS :=	$(wildcard src/*.cpp)

# Object
# /OBJS :=	$(SRCS:.cpp=.o)
# OBJDIR := obj/
# _OBJS	= $(patsubst src/%.cpp, %.o, $(SRC))
# OBJS	= $(addprefix $(OBJDIR), $(_OBJS))

# Flag
# CXXFLAGS :=	-Wall -Werror -Wextra -pedantic -std=c++98
CXXFLAGS :=	-std=c++98

# C++ Compiler
CXX := clang++

# Build
$(PROG): $(OBJS)
	@echo $(SRCS)
	@$(CXX) $(OBJS) -lncurses -o $@
	@echo "$(G)Done!$(E)"

$(OBJS): $(SRCS)
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# All
all: $(PROG)
	@echo $(SRCS)

# Clean
clean:
			@rm -f $(OBJS)
			@echo "$(R)Cleaned!$(E)"
fclean:     clean
			@rm -f $(PROG)
			@echo "$(P)Cleaned Everything!$(E)"

# Rebuild
re:			fclean all

# Redundency | GNU still runs if files with names below exist
.PHONY:
			all clean fclean re