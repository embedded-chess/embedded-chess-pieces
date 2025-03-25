# Embedded Chess Pieces

This repository is a fork of [`dezibot/dezibot`](https://github.com/dezibot/dezibot) and contains our project for the module C999 "Software Development for Embedded Systems" lectured by [Prof. Dr. rer. nat. Jens Wagner](https://fim.htwk-leipzig.de/fakultaet/personen/professorinnen-und-professoren/jens-wagner/). We call it *Embedded Chess Pieces*.


## Idea

The idea is to place a Dezibot4 on a chess board and assign a chess piece to it. The user can select which piece the robot represents and how it should move. The selected figure shall be displayed on the built-in display and the move shall be validated first. The result should be shown via the built-in LEDs.


## Usage

Example sketches are provided under [`example/EmbeddedChessPieces/examples/playground/playground.ino`](./example/EmbeddedChessPieces/examples/playground/playground.ino) to demonstrate the library, while a showcase sketch can be found under [`/example/EmbeddedChessPieces/examples/showcase/embedded_chess_piece/embedded_chess_piece.ino`](./example/EmbeddedChessPieces/examples/showcase/embedded_chess_piece/embedded_chess_piece.ino). They can be loaded on the Dezibot that will simulate the chess piece. On an additional Dezibot (*beacon*), the [`beacon/beacon.ino`](./example/EmbeddedChessPieces/examples/beacon/beacon.ino) sketch needs to be installed, to guide the simulating Dezibot's rotations. The beacon has to be placed next to the field, facing approximately the middle of the chess board. For more information, see the [documentation](https://github.com/embedded-chess/doc/releases) (German only).


## Repository Structure

This repository is a fork of [`dezibot/dezibot`](https://github.com/dezibot/dezibot). Changes to the `dezibot` library are made directly where necessary. Our main contribution, the `EmbeddedChessPieces` library, is stored in [`example/EmbeddedChessPieces/`](./example/EmbeddedChessPieces/). It includes project specific code that is not generally sensible to add to the `dezibot` library.

In [`example/EmbeddedChessPieces/examples`](./example/EmbeddedChessPieces/examples/) you can find tests and example use cases for our project. This includes Arduino sketches we have developed to test our library as well as the heart of this project – the code to run our project. You can also find a [`showcase`](./example/EmbeddedChessPieces/examples/showcase/) directory which demonstrates the possibilities offered by this library. In [`examples/playground/playground.ino`](./example/EmbeddedChessPieces/examples/playground/playground.ino), a step by step guide is provided.


## Context

| Context    | Description                                                                         |
|------------|-------------------------------------------------------------------------------------|
| Module     | C999 Software Development for Embedded Systems                                      |
| Lecturer   | Prof. Dr. rer. nat. Jens Wagner, M. Eng. Marian Ulbricht                            |
| Institute  | Leipzig University of Applied Sciences                                              |
| Semester   | Winter Semester 2024/25                                                             |


## Installation

- Install [Arduino IDE 2](https://github.com/arduino/arduino-ide)
- Add [`esp32`](https://github.com/espressif/arduino-esp32/releases/tag/2.0.15) board manager by Espressif Systems (version 2.0.15)
- Install all necessary libraries mentioned under [License](#license)
- Create a symbolic link from this repository and the `EmbeddedChessPieces` library to the Arduino library directory on your machine

```sh
cd path/to/Arduino/library
ln -s path/to/repository Dezibot
ln -s path/to/repository/example/EmbeddedChessPieces EmbeddedChessPieces
```


## Team

- [@irooori](https://github.com/irooori)
- [@nicosrm](https://github.com/nicosrm)


## License

This repository is licensed under the GNU General Public License ([GPL-3.0](./LICENSE.txt)).

We also require using the following (third-party) libraries that are licensed as follows:

| Library                                                               | Version | Author       | License      |
|-----------------------------------------------------------------------|---------|--------------|--------------|
| [`Adafruit NeoPixel`](https://github.com/adafruit/Adafruit_NeoPixel)* | 1.12.3  | Adafruit     | LGPL-3.0     |
| [`ArduinoJson`](https://github.com/bblanchon/ArduinoJson)*            | 7.2.0   | bblanchon    | MIT          |
| [`AsyncTCP`](https://github.com/dvarrel/AsyncTCP)*                    | 1.1.4   | dvarrel      | LGPL-3.0     |
| [`Dezibot`](https://github.com/dezibot/dezibot) (modified)            | -       | dezibot      | GPL-3.0      |
| [`Painless Mesh`](https://gitlab.com/painlessMesh/painlessMesh)*      | 1.5.0   | PainlessMesh | GPL-3.0      |
| [`TaskScheduler`](https://github.com/arkhipenko/TaskScheduler)*       | 3.8.5   | arkhipenko   | BSD-3-Clause |
| [`VEML6040`](https://github.com/thewknd/VEML6040)*                    | 0.3.2   | thewknd      | MIT          |

`*`: Dependency of Dezibot library
