CXX 		   	:= g++
CXX_FLAGS		:= -std=c++2a -lsfml-window -lsfml-graphics -lsfml-system

CXX_DEBUG_FLAGS := -O0 -ggdb3

# CXX_DEBUG_FLAGS := -O0 -ggdb3 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -fPIE -pie -Wlarger-than=8192 -Wstack-usage=8192

PROGRAM_NAME	:= shopofot
PROGRAM_OUT		:= $(addsuffix .out, $(PROGRAM_NAME))

INCLUDE_DIRS	:= include/ src/

 SOURCE_DIR		:= src/
 SOURCE_DIRS	:= util/list/ util/sfml/ widget/ universal_layoutbox/ math/transform/ math/transform_stack/ math/vec2d/ ui/button/button/ event/event/ event/event_manager/ graphics/render_texture/ graphics/render_window/ graphics/shapes/

BUILD_DIR		:= build/

OBJ_DIR			:= $(BUILD_DIR)

BUILD_DIR_DEP	:= $(addsuffix .dirstamp, $(BUILD_DIR) $(addprefix $(OBJ_DIR), $(SOURCE_DIRS)))

SOURCE_DIRS		:= $(SOURCE_DIR) $(addprefix $(SOURCE_DIR), $(SOURCE_DIRS))
SOURCE_FILES	:= $(wildcard $(addsuffix *.cpp, $(SOURCE_DIRS)))

DEP_FILES 		:= $(SOURCE_FILES:.cpp=.d)

OBJECT_FILES	:= $(patsubst src/%.cpp, $(OBJ_DIR)%.o, $(SOURCE_FILES))

BUILD_LOG_NAME	:= build
BUILD_LOG		:= $(BUILD_DIR)$(BUILD_LOG_NAME).log

all: $(BUILD_DIR_DEP) $(PROGRAM_OUT)

$(PROGRAM_OUT): $(OBJECT_FILES)
	@echo [$(shell date -Iseconds)] CXX $@ | tee -a $(BUILD_LOG)
	@$(CXX) $^ -o $@ $(CXX_FLAGS) | tee -a $(BUILD_LOG)

$(OBJ_DIR)%.o: $(SOURCE_DIR)%.cpp $(BUILD_DIR_DEP)
	@echo [$(shell date -Iseconds)] CXX $< | tee -a $(BUILD_LOG)
	@$(CXX) $< -c $(CXX_FLAGS) $(addprefix -I, $(INCLUDE_DIRS)) -o $@ -MMD | tee -a $(BUILD_LOG)

%/.dirstamp:
	@mkdir -p $(dir $@) && touch $@
	@echo [$(shell date -Iseconds)] mkdir $(dir $@) | tee -a $(BUILD_LOG)

sinclude $(DEP_FILES)

clean:
	@rm -r $(BUILD_DIR) $(DEP_FILES) build.log

