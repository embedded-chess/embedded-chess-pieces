# IR Sensors

This directory contains four sketches regarding infrared sensors.

- `ir_colour_detection.ino` is a test sketch for field colour detection using the infrared LED on the bottom of the dezibot. It first calibrates itself (see [`ECPColorDetection`](../../../src/ECPColorDetection/ECPColorDetection.h)).
- `ir_emitter.ino` emits an infrared signal from the dezibot. This sketch is needed for the rotation functions in *Embedded Chess Pieces* as a guide for the dezibot (see [`ECPMovement`](../../../src/ECPMovement/ECPMovement.h)).
- `ir_emitter_ir_color_detection.ino` emits an infrared signal when no other signal is measured at the front of the dezibot. It measures it's own IR signal causing it to periodically turn on and off, if no other signal is measured in between.
- `ir_sensors.ino` is a test sketch to validate the angle measurements and calculations of [`ECPSignalDetection`](../../../src/ECPSignalDetection/ECPSignalDetection.h). It calculates the angle of the signal relative to the dezibot and infers the angle the dezibot is facing.
