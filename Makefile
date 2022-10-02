CPP = clang++
CPP_FLAGS = -g -W -std=c++11 -larmadillo -llapack

msg:
	@echo 'Valid options for compiling:'
	@echo 'lmu - compiles main LMU files'
	@echo 'tests - compiles and runs test files'
	@echo 'audio - compiles LMU and audio processing files'
	@echo 'pybind - compiles with wrappers for Python'
	@echo 'jsbind - compiles with wrappers for JavaScript'
	@echo 'clean - removes all generated files'

lmu: src/lmu/lmuCell.cpp src/lmu/lmuLayer.cpp
	${CPP} ${CPP_FLAGS} -c src/lmu/lmuCell.cpp -o build/lmuCell.o
	${CPP} ${CPP_FLAGS} -c src/lmu/lmuLayer.cpp -o build/lmuLayer.o

clean:
	rm build/*.o 