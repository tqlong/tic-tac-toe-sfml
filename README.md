# Tic Tac Toe
An implementation of Tic Tac Toe game using SFML framework

## Clone source
```
git clone --recursive https://github.com/tqlong/tic-tac-toe-sfml
```
or
```
git clone https://github.com/tqlong/tic-tac-toe-sfml
cd tic-tac-toe-sfml
git submodule update --init --recursive
```

## Build via Makefile
```
make
./tic-tac-toe
```

## Build via cmake (more general)
```
mkdir build
cd build
cmake ..
make
./tic-tac-toe
```

## Unit tests
```
make test
```