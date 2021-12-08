
CONTENT OF THIS FILE
--------------------

* Introduction
* Installation
* Starting the Game Engine
* Using the Game Engine
* Camera Controls

INTRODUCTION
------------

Current Maintainer: Alvaro Soppelsa <alvarosoppelsa@gmail.com>

GameEngine is an open source, easy to use & totally free game engine that has been developed for the UPC Master Degree 'Advance Programming for AAA Video Games'
His main pourpose is to load and render 3D modules and have several settings to inspect them.
It is based on SDL, Glew, ImGui, DevIl and MathGeoLib libraries.

INSTALLATION
------------

This software consist on an stand alone executable, so doesn't need to be installed on the system.

STARTING THE GAME ENGINE
------------------------

Running the binary 'GameEngine.exe' you should be able to start it. Once open, the program load BakerHouse.fbx automatically and you will be able to see General Settings window.

USING THE GAME ENGINE
---------------------

In General Settings you will have most of the configurations availables.

Windows Settings:
  - Fullscreen
  - Vsync

Camera Settings:
  - Translation (Position) of the camera
  - Camera Speed
  - Horizontal Field of View

Module Info: Retrieves information about the loaded module

System: Let the user know about memory consumption in real time

In 'Editor Tools' you will find the Console that print usefull information and Performance Plots that print FPS and delta time.

In Main Menu Bar, you can Close the program by doing File->Close and watch About window.

CAMERA CONTROLS
---------------
 <pre>
  Action                Key
--------------------------------
- Move Forward          W
- Move Backward         S
- Move Right            D
- Move Left             A
- Rotate Up             Up arrow
- Rotate Down           Down arrow
- Rotate Right          Right arrow
- Rotate Left           Left arrow
- + Horiz FOV           Q
- - Horiz FOV           E
- Double Speed          SHIFT (holding)
- Free rotation         Mouse Right Click (holding)
- Orbit Module          ALT + Mouse Left Click (only if a module is loaded)
- Zoom In/out           Scrolling
</pre>
