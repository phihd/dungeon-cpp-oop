Source code, makefiles, etc. here.  
Please update the progress log, any notes, etc.

### 17 Nov 2020
Phi:
- Add Enemy, Ally classes
- Item now has price, description, and stat (which increase a flat amount of stat for a unit). 
- Stat now has operator +, allow easier adjusting stat for units
- Implement methods of class Player, allow a player to interact with items and units.  
Khoa:
- Add one more type of Square: Treasure
- Create abstract class Room, class Rest inherited from Room and rename class Room to Battlefield. Class Battlefield inherit from both Room and Grid
- Implement FromString and ToString in Battlefield for saving and create rooms from strings/files
- Implement Buy, Sell and Rest in class Rest

Mai:
- Create MVS project
- Add SFML files
- Add and link SFML libraries to the dungeon folder
- Create the grid map and change color of the square if it is clicked

Taige: 
- Updated CMakeLists file, VSCode configuration file, made SFML library to work
- Tried CTest testing framework


### 9 Nov 2020  
Khoa: 
- Created Square.hpp, Grid.hpp, Room.hpp, World.hpp 

Phi
- Created Player, Item, Unit, Stat class

Taige
- Added .gitignore, added Makefile config (will be ready later this week)