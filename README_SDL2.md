Installing SDL2
---------------

To install SDL2 in your own home directory, follow these directions:

1. Download SDL2:
   ``` wget https://www.libsdl.org/release/SDL2-2.0.3.tar.gz ```

2. Decompress the downloaded archive to a destination of your choice. For example:
   ``` tar xvzf SDL2-2.0.3.tar.gz -C ~/build ```

3. Enter the SDL directory:
   ``` cd SDL2-2.0.3 ```

4. Configure the build, adding the "--prefix" flag to set the install destination. For example:
   ``` ./configure --prefix=/home/uhenc/lib/SDL2 ```
   Notice that I've entered an absolute path for the prefix. Relative paths are not allowed. :(

5. Build and install SDL2:
   ``` make && make install ```

6. Navigate to where the game code is and build it. For example:
   ``` g++ -Wall -g -L/home/uhenc/lib/SDL2/lib -I/home/uhenc/lib/SDL2/include -lSDL2 -std=c++11 game.cpp engine/*.cpp -o game ```