all:
	make -C build -j 4
	tput sgr0

cmake:
	cmake -B build -G "Unix Makefiles" -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang -DCMAKE_EXPORT_COMPILE_COMMANDS=1
	make

full:
	rm -rf build
	make cmake

fullrun:
	make full
	make run

run:
	build\Voxel.exe