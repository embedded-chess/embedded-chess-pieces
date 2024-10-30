# Embedded Chess Pieces

This repository contains our project for the module C999.1 "Software Development for Embedded Systems" lectured by [Prof. Dr. rer. nat. Jens Wagner](https://fim.htwk-leipzig.de/fakultaet/personen/professorinnen-und-professoren/jens-wagner/). We call it *Embedded Chess Pieces*.

> [!IMPORTANT]
> The project is still under development. This note will be removed once the project is submitted.


## Idea

The idea is to place a Dezibot 4 on a chess board and assign a chess piece to it. The user can select which piece the robot represents and how it should move via a wireless connection. The selected figure shall be displayed on the built-in display. If there is time, the move shall be validated first and be shown via the LEDs.


## Repository Structure

Our contribution is placed in [`example/embedded_chess_pieces/`](./example/embedded_chess_pieces/).
<!-- TODO: State changes -->


## Context

| Context    | Description                                                                         |
|------------|-------------------------------------------------------------------------------------|
| Module     | C377.2 Prinzipien von Programmiersprachen                                           |
| Lecturer   | Prof. Dr. rer. nat. Jens Wagner, M. Eng. Marian Ulbricht                            |
| Institute  | Leipzig University of Applied Sciences                                              |
| Semester   | Winter Semester 2024/25                                                             |


## Roadmap

- [ ] Recognise colours of the chess board [#1](/../../issues/1)
- [ ] Simulate Pawn [#4](/../../issues/4)
    - [ ] Walk straight a specified number of fields [#2](/../../issues/2)
    - [ ] Turn in a given direction to simulate diagonal movement [#3](/../../issues/3)
- [ ] Find centre of a chess field [#5](/../../issues/5)
- [ ] Draw selected figure to the display [#6](/../../issues/6)
- [ ] Logic on which field the robot is at any given moment (show on the display if shaken) [#7](/../../issues/7)
- [ ] Wireless connection for initial field and movements [#8](/../../issues/8)
- [ ] Expand selectable pieces [#9](/../../issues/9)
- [ ] Validate if move is allowed and colour LED green or red accordingly [#10](/../../issues/10)


## Usage

- Install [Arduino IDE 2](https://github.com/arduino/arduino-ide)
- Add [`esp32`](https://github.com/espressif/arduino-esp32/releases/tag/2.0.15) board manager by Espressif Systems (version 2.0.15)
- Install the following libraries
    - [`Adafruit NeoPixel`](https://github.com/adafruit/Adafruit_NeoPixel) by Adafruit
    - [`Painless Mesh`](https://gitlab.com/painlessMesh/painlessMesh/-/tree/v1.5.0) by painlessMesh (version 1.5.0) including dependencies
    - [`AsyncTCP`](https://github.com/dvarrel/AsyncTCP/releases/tag/1.1.4) by dvarrel (version 1.1.4)
    - [`VEML6040`](https://github.com/thewknd/VEML6040/) by thewknd (included as [submodule](./libraries/VEML6040/))
- In Arduino IDE, open preferences and select the root directory of this repository as your sketchbook location


## Team

- [@irooori](https://github.com/irooori)
- [@nicosrm](https://github.com/nicosrm)

## Licence

This repository is licenced under the GNU General Public License ([GPL-3.0](./LICENSE)).
<!-- TODO: State changes -->
