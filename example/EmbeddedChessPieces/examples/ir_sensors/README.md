# IR Sensors

This directory contains two sketches regarding infrared sensors.

- `ir_emitter.ino` emits an infrared signal from the dezibot. This sketch is needed for the rotation functions in *Embedded Chess Pieces* as a guide for the dezibot (see [`ECPMovement`](../../src/ECPMovement/ECPMovement.h)).
- `ir_sensors.ino` is a test sketch to validate the angle measurements and calculations of [`ECPSignalDetection`](../../src/ECPSignalDetection/ECPSignalDetection.h). It calculates the angle of the signal relative to the dezibot and infers the angle the dezibot is facing.