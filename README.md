# 42_so_long

Game Rules
The game we choose must follow a set of rules. The executable so_long will receive a map as the only argument, and this map will have a .ber filetype.

The file also must follow these rules:

Only P (pacman), 1 (wall), 0 (empty), C (collectible), and E (exit) will be accepted characters in our map (except if you add enemies as bonus)
The map must be rectangular, i.e. all rows must have the same length
There must be at least one exit, one player, and one collectible on the map
The map must be closed, i.e. surrounded by walls
If any of these checks fail, the game must end with Error\n followed by a custom message.

The goal is for the player(s) to collect all the collectibles on the map before going to an exit in the least possible number of steps


# How it Works

For the graphics part of the project we used a library called minilibx. It's fairly basic and somewhat limited, but was still fun to use in the project.

# Cloning the repositories

git clone https://github.com/hrinka/42_so_long.git

cd 42_so_long

make
