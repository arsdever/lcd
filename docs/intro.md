# 1. Introduction

The simulation of the LCD controller is based on the HD44780 microcontroller.

The controller implementation is separate from the display implementation,
which makes it easier to use the same controller to instantiate different
sizes and models of display. It also comes as a separate library, which can be
used as a back-end for different front-end implementations.

## 1.2 Details

Currently, there is only one GUI implementation based on [Qt](https://github.com/qt/qt5)
library. But it's very simple to have your own implementation.
