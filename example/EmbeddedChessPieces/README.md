# Embedded Chess Pieces Library

This is a library for the [Dezibot](https://github.com/dezibot/dezibot) providing classes and helper for the *Embedded Chess Pieces* project. For more information, please checkout the [original repository](https://github.com/nicosrm/24-emb-chess/) or [documentation](https://github.com/embedded-chess/doc/releases) (German only).


## Idea

The idea is to place a Dezibot4 on a chess board and assign a chess piece to it. The user can select which piece the robot represents and how it should move. The selected figure shall be displayed on the built-in display and the move shall be validated first. The result should be shown via the built-in LEDs.


## Usage

Example sketches are provided under [`examples/playground/playground.ino`](./examples/playground/playground.ino) to demonstrate the library, while a showcase sketch can be found under [`examples/showcase/embedded_chess_piece/embedded_chess_piece.ino`](./examples/showcase/embedded_chess_piece/embedded_chess_piece.ino) to illustrate the movements. They can be loaded on the Dezibot that will simulate the chess piece. On an additional Dezibot (*beacon*), the [`beacon/beacon.ino`](./examples/beacon/beacon.ino) sketch needs to be installed, to guide the simulating Dezibot's rotations. The beacon has to be placed next to the field, facing approximately the middle of the chess board. For more information, see the [documentation](https://github.com/embedded-chess/doc/releases) (German only).


## Library Structure

Our main contribution, the `EmbeddedChessPieces` library, is stored in [`src`](./src). It includes project specific code that is not generally sensible to add to the `dezibot` library.

In [`examples`](./examples) you can find tests and example use cases for our project. This includes Arduino sketches we have developed to test our library as well as the heart of this project – the code to run our project. You can also find a [`showcase`](./examples/showcase/) directory which demonstrates the possibilities offered by this library. In [`examples/playground/playground.ino`](./examples/playground/playground.ino), a step by step guide is provided.


## Context

| Context    | Description                                                                         |
|------------|-------------------------------------------------------------------------------------|
| Module     | C999 Software Development for Embedded Systems                                      |
| Lecturer   | Prof. Dr. rer. nat. Jens Wagner, M. Eng. Marian Ulbricht                            |
| Institute  | Leipzig University of Applied Sciences                                              |
| Semester   | Winter Semester 2024/25                                                             |


## Installation

- Follow installation guide for `dezibot` library.
- Additionally, create a symbolic link from this directory to the Arduino library directory on your machine.

```sh
cd path/to/Arduino/library
ln -s path/to/repository/example/EmbeddedChessPieces EmbeddedChessPieces
```


## Team

- [@irooori](https://github.com/irooori)
- [@nicosrm](https://github.com/nicosrm)


## License

This library was written by [@irooori](https://github.com/irooori) and [@nicosrm](https://github.com/nicosrm). It is available under the GNU General Public License ([GPL-3.0](./LICENSE)).
