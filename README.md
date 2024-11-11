# Embedded Chess Pieces

This repository contains our project for the module C999.1 "Software Development for Embedded Systems" lectured by [Prof. Dr. rer. nat. Jens Wagner](https://fim.htwk-leipzig.de/fakultaet/personen/professorinnen-und-professoren/jens-wagner/). We call it *Embedded Chess Pieces*.

> [!IMPORTANT]
> The project is still under development. This note will be removed once the project is submitted.


## Idea

The idea is to place a Dezibot 4 on a chess board and assign a chess piece to it. The user can select which piece the robot represents and how it should move via a wireless connection. The selected figure shall be displayed on the built-in display. If there is time, the move shall be validated first and be shown via the LEDs.


## Repository Structure

This repository is structured as follows. All libraries we developed (further) are stored in [`libraries`](./libraries/). This includes changes to the [`Dezibot` library](./libraries/Dezibot/) and the completely newly developed [`EmbeddedChessPieces` library](./libraries/EmbeddedChessPieces/). The latter one includes project specific code that is not generally sensible to add to the Dezibot library.

In `src` you can find example use cases for our project. This includes Arduino sketches we developed to test our library developments as well as the heart of this project – the code to run our project.


## Context

| Context    | Description                                                                         |
|------------|-------------------------------------------------------------------------------------|
| Module     | C377.2 Prinzipien von Programmiersprachen                                           |
| Lecturer   | Prof. Dr. rer. nat. Jens Wagner, M. Eng. Marian Ulbricht                            |
| Institute  | Leipzig University of Applied Sciences                                              |
| Semester   | Winter Semester 2024/25                                                             |


## Roadmap

- [x] Recognise colours of the chess board [#1](https://github.com/nicosrm/24-emb-chess/issues/1)
- [ ] Simulate Pawn [#4](https://github.com/nicosrm/24-emb-chess/issues/4)
    - [ ] Walk straight a specified number of fields [#2](https://github.com/nicosrm/24-emb-chess/issues/2)
    - [ ] Turn in a given direction to simulate diagonal movement [#3](https://github.com/nicosrm/24-emb-chess/issues/3)
- [ ] Find centre of a chess field [#5](https://github.com/nicosrm/24-emb-chess/issues/5)
- [ ] Draw selected figure to the display [#6](https://github.com/nicosrm/24-emb-chess/issues/6)
- [ ] Logic on which field the robot is at any given moment (show on the display if shaken) [#7](https://github.com/nicosrm/24-emb-chess/issues/7)
- [ ] Calibrate black / white threshold [#15](https://github.com/nicosrm/24-emb-chess/issues/15)
- [ ] Wireless connection for initial field and movements [#8](https://github.com/nicosrm/24-emb-chess/issues/8)
- [ ] Expand selectable pieces [#9](https://github.com/nicosrm/24-emb-chess/issues/9)
- [ ] Validate if move is allowed and colour LED green or red accordingly [#10](https://github.com/nicosrm/24-emb-chess/issues/10)


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

We also use the following third-party libraries that are licenced as follows:

| Library                                                              | Version | Author       | Licence      |
|----------------------------------------------------------------------|---------|--------------|--------------|
| [`Adafruit NeoPixel`](https://github.com/adafruit/Adafruit_NeoPixel) | 1.12.3  | Adafruit     | LGPL-3.0     |
| [`ArduinoJson`](https://github.com/bblanchon/ArduinoJson)            | 7.2.0   | bblanchon    | MIT          |
| [`AsyncTCP`](https://github.com/dvarrel/AsyncTCP)                    | 1.1.4   | dvarrel      | LGPL-3.0     |
| [`Dezibot`](https://github.com/dezibot/dezibot) (modified)           | -       | dezibot      | GPL-3.0      |
| [`Painless Mesh`](https://gitlab.com/painlessMesh/painlessMesh)      | 1.5.0   | PainlessMesh | GPL-3.0      |
| [`TaskScheduler`](https://github.com/arkhipenko/TaskScheduler)       | 3.8.5   | arkhipenko   | BSD-3-Clause |
| [`VEML6040`](https://github.com/thewknd/VEML6040)                    | 0.3.2   | thewknd      | MIT          |
