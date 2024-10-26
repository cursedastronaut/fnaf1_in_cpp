#
# Cross Platform Makefile
# Compatible with MSYS2/MINGW, Ubuntu 14.04.1 and Mac OS X
#
# You will need GLFW (http://www.glfw.org):
# Linux:
#   apt-get install libglfw-dev
# Mac OS X:
#   brew install glfw
# MSYS2:
#   pacman -S --noconfirm --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-glfw
#

#CXX = g++
#CXX = clang++

EXE = fnaf_in_cpp
INC_DIR = include
IMGUI_DIR = $(INC_DIR)/imgui
SOURCES = main.cpp
OBJ_DIR = .objects
SRC_DIR = src
SRCGAME_DIR = src/game
SOURCES_GAME = $(SRCGAME_DIR)/bonnie.c $(SRCGAME_DIR)/chica.c $(SRCGAME_DIR)/foxy.c $(SRCGAME_DIR)/freddy.c $(SRCGAME_DIR)/game.c $(SRCGAME_DIR)/player.c $(SRCGAME_DIR)/constants.c
OBJS_SRCGAME = $(addprefix $(SRCGAME_DIR)/, $(addsuffix .o, $(basename $(notdir $(SOURCES_GAME)))))

SOURCES_IMGUI += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES_IMGUI_B += $(IMGUI_DIR)_backends/imgui_impl_glfw.cpp $(IMGUI_DIR)_backends/imgui_impl_opengl3.cpp
OBJS_IMGUI = $(addprefix $(IMGUI_DIR)/, $(addsuffix .o, $(basename $(notdir $(SOURCES_IMGUI)))))
OBJS_IMGUI_BACKEND = $(addprefix $(IMGUI_DIR)_backends/, $(addsuffix .o, $(basename $(notdir $(SOURCES_IMGUI_B)))))
SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/resources.cpp $(SRC_DIR)/game.cpp $(SRC_DIR)/displaying.cpp
OBJS_SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))

OBJS = $(OBJS_SRC)
OBJS += $(OBJS_IMGUI)
OBJS += $(OBJS_IMGUI_BACKEND)
OBJS += $(OBJS_SRCGAME)

UNAME_S := $(shell uname -s)
LINUX_GL_LIBS = -lGL

CXXFLAGS = -std=c++17 -I$(IMGUI_DIR) -I$(IMGUI_DIR)_backends -I$(INC_DIR)
CCFLAGS = -g -Wall -Wformat -Wextra
CXXFLAGS += $(CCFLAGS)
LIBS =

##---------------------------------------------------------------------
## OPENGL ES
##---------------------------------------------------------------------

## This assumes a GL ES library available in the system, e.g. libGLESv2.so
# CXXFLAGS += -DIMGUI_IMPL_OPENGL_ES2
# LINUX_GL_LIBS = -lGLESv2

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	LIBS += $(LINUX_GL_LIBS) `pkg-config --static --libs glfw3`

	CXXFLAGS += `pkg-config --cflags glfw3`
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(UNAME_S), Darwin) #APPLE
	ECHO_MESSAGE = "Mac OS X"
	LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
	LIBS += -L/usr/local/lib -L/opt/local/lib -L/opt/homebrew/lib
	#LIBS += -lglfw3
	LIBS += -lglfw

	CXXFLAGS += -I/usr/local/include -I/opt/local/include -I/opt/homebrew/include
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(OS), Windows_NT)
	ECHO_MESSAGE = "MinGW"
	LIBS += -lglfw3 -lgdi32 -lopengl32 -limm32

	CXXFLAGS += `pkg-config --cflags glfw3`
	CFLAGS = $(CXXFLAGS)
endif

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

$(OBJ_DIR)/$(SRCGAME_DIR)%.o:$(SRCGAME_DIR)/%.c
	$(CXX) $(CCFLAGS) -c -o $@ $<
$(OBJ_DIR)/$(SRC_DIR)%.o:$(SRC_DIR)%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/$(IMGUI_DIR)/%.o:$(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/$(IMGUI_DIR)_backends/%.o:$(IMGUI_DIR)_backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(addprefix $(OBJ_DIR)/, $(OBJS))
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(EXE) $(addprefix $(OBJ_DIR)/, $(OBJS))
