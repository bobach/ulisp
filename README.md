# uLisp - Refactored
This is a fork of uLisp. Goal of this fork is to refactor the project to multiple accesible files, add support for Arduino-mk, and add commentery. 

Basic idea is to split all of the files by use, and try to split hardware handling functions from actual lisp handling functions. 

Reasons for this fork:
* Arduino IDE is terrible and will hold back further development
* Structured project is a sane way to support multiple architectures
* Arduino-mk is pretty amazing
* Ability to use standard programming tools like gdb, screen for serial comms
* Since Arduino IDE does a lot of preprocesing for you, you can get away with a lot of non standard C++, that should be changed to proper library format.
* Having the project split across files increases git effectiveness and can increase collaboration.
* And most importantly this is an learning exercise for me, but feel free to criticize my refactor decisions :) 

Since this repo *will* be harder to develop inside Arduino IDE, I don't know if its mergable with the main project. 
See [Why are sources in single file](http://www.ulisp.com/show?2ECM)

## How to try it
* Install [Arduino-mk](https://github.com/sudar/Arduino-Makefile)
* Make modifications to Makefile in this project for your board
* make
* make upload
* make monitor


Currently will be only tested on ATmega1284P and ATmega328P. 
A version of the Lisp programming language for ATmega-based Arduino boards.

For more information see:
http://www.ulisp.com/
