build:
	mkdir -p build
	ln -svf `pwd`/assets build/assets
	cd build && cmake ../src && make

run: build
	cd build && ./game
