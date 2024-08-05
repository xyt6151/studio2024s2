
## Microcontroller Sketches & Libraries

### Sketches
- full_sketch/full_sketch.ino - Sketch for the full featured iteration of the working prototype
- menu_test_for_wokwi/main.ino - A version of the full sketch, modified to function without the CH446Q functionality or any actual microcontrollers connected to the project mainboard. This sketch is only for testing how the menu code interacts with the information stored in structs etc

### Libraries used in full_sketch.ino
- DevicesAndInterconnects - A custom library created for this project. It provides easy-to-use frontend functions for adding/modifying/removing/using the various pieces of information used to define microcontrollers, pins, CH446Q connections, etc. 
- Liq
