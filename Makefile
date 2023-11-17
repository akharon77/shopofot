CXX = g++
CXX_FLAGS = -fPIC -I ~/Projects/shopofot -ggdb3 -mavx512vl -mavx512f -mavx512cd -mavx512dq -std=c++2a -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -lsfml-graphics -lsfml-window -lsfml-system

BIN  = shopofot.out
SRC  = $(wildcard *.cpp)
OBJ  = $(patsubst %.cpp,%.o,$(SRC))
DEP  = $(patsubst %.cpp,%.d,$(SRC))

all: $(BIN)

$(BIN): $(OBJ) filter_plugins/brightness_filter.so
	$(CXX) $(OBJ) -o $@ $(CXX_FLAGS)

-include $(DEP)

filter_plugins/brightness_filter.so: filter_plugins/brightness_filter.o
	g++ -shared filter_plugins/brightness_filter.o canvas.o -o filter_plugins/brightness_filter.so

filter_plugins/brightness_filter.o: filter_plugins/brightness_filter.cpp
	g++ -I ~/Projects/shopofot -Wall -c -fPIC filter_plugins/brightness_filter.cpp -o filter_plugins/brightness_filter.o -static

%.o: %.cpp
	$(CXX) -MMD -c $< -o $@ $(CXX_FLAGS)

clean:
	rm -rf $(DEP) $(OBJ) $(BIN)
	rm -rf filter_plugins/*.o
	rm -rf filter_plugins/*.so

