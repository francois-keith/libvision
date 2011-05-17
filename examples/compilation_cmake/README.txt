Compiling an example with Cmake.
--------------------------------


What you need :

	- A Working version of cmake
	- The vision library installed somewhere

How to :

	1. Create a new sub directory called 'build' 
	(or whatever you want, who cares anyway ?)

	 > cd /usr/share/example/lib_vision/examples/compilation_cmake
	 > mkdir build
	 > cd build

	2. Run cmake in this directory

	 > cmake ..

	 If you prefer, you can use the graphical interface :
	
	 > ccmake ..
	   then press c twice and g

	3. Compile

	 > make

	4. Run

	 > ./example test.png output.png

	 This will create the file output.png.

