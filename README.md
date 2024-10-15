# Embedded Chess Figures

This repository contains our project for the module C999.1 "Software Development for Embedded Systems" lectured by [Prof. Dr. rer. nat. Jens Wagner](https://fim.htwk-leipzig.de/fakultaet/personen/professorinnen-und-professoren/jens-wagner/). We call it *Embedded Chess Figures*.

> [!IMPORTANT]
> The project is still under development. This note will be removed once the project is submitted.


## Idea

The idea is to place a Dezibot 4 on a chess board and assign a chess piece to it. The user can select which piece the robot represents and how it should move via a wireless connection. The selected figure shall be displayed on the built-in display. If there is time, the move shall be validated first and be shown via the LEDs.


## Repository Structure

Our contribution is placed in [`./example/embedded_chess_figures/`](./example/embedded_chess_figures/).
<!-- TODO: State changes -->


## Context

| Context    | Description                                                                         |
|------------|-------------------------------------------------------------------------------------|
| Module     | C377.2 Prinzipien von Programmiersprachen                                           |
| Lecturer   | Prof. Dr. rer. nat. Jens Wagner, M. Eng. Marian Ulbricht                            |
| Institute  | Leipzig University of Applied Sciences                                              |
| Semester   | Winter Semester 2024/25                                                             |


## Roadmap

- [ ] Recognise colours of the chess board
- [ ] Find centre of a chess field
- [ ] Simulate Pawn
    - [ ] Walk straight a specified number of fields
    - [ ] Turn in a given direction to simulate diagonal movement
- [ ] Draw selected figure to the display
- [ ] Logic on which field the robot is at any given moment (show on the display if shaken)
- [ ] Wireless connection
    - [ ] Decide whether to use WLAN or Bluetooth
    - [ ] Establish connection
    - [ ] Communicate initial field
    - [ ] Communicate fields to move
- [ ] Expand selectable figures
    - [ ] Tower
    - [ ] King
    - [ ] Knight
    - [ ] Bishop
    - [ ] Queen
- [ ] Validate if move is allowed
    - [ ] Colour LED green or red


## Team

- [@irooori](https://github.com/irooori)
- [@nicosrm](https://github.com/nicosrm)


## Licence

This repository is licenced under the GNU General Public License ([GPL-3.0](./LICENSE.txt)).
<!-- TODO: State changes -->
