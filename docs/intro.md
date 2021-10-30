# 1. Introduction

The simulation of the LCD controller is based on the HD44780 microcontroller.

The controller implementation is separate from the display implementation,
which makes it easier to use the same controller to instantiate different
sizes and models of display. It also comes as a separate library, which can be
used as a back-end for different front-end implementations.
