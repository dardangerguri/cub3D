# cub3D

The cub3D is an engaging game engine that uses ray-casting techniques similar to the classic game Wolfenstein 3D.

<img src="https://github.com/dardangerguri/cub3D/blob/master/cub3d.gif" alt="cub3d"/>

## About the project

The objective of cub3D is to build a 3D maze environment using ray-casting techniques. The program renders the environment in a window, allowing players to explore and interact with the maze. Developed as part of the 42 school curriculum, cub3D offers developers an opportunity to explore graphics programming and game development concepts.

### Project features

- Utilizes ray-casting techniques to create a 3D maze environment.
- Renders different wall textures based on the orientation (North, South, East, West).
- Allows customization of floor and ceiling colors.
- Supports player movement and view rotation using keyboard controls.
- Provides a smooth window management experience.
- Error handling

### Constrains

- Window management must remain smooth, including window switching and minimizing.
- Map composition is limited to six possible characters: 0 (empty space), 1 (wall), and N/S/E/W (player's start position and orientation).
- Map must be surrounded by walls, and other elements of the map must be separated by one or more empty lines.
- Each type of element in the scene description file can be set in any order and must follow a specific format.

### Bonus

- There is a minimap on the bonus part.

<img src="https://github.com/dardangerguri/cub3D/blob/master/fadingSky.gif" alt="Fading Sky" width="600" height="300"/>

Below is a valid format of the map file: 
``` text
NO ./textures/wolf/wood.png
SO ./textures/wolf/redbrick.png
WE ./textures/wolf/pillar.png
EA ./textures/wolf/eagle.png
F 210,50,100
C 20,250,100

111111111111111111111
100000000000000000001
100011001111111111111
100N00001
111111111
```

## Running the project

To run the project, first clone the repository and navigate into the project directory. Then, use the `make` command to compile the project.

Once the project is compiled, you can run it with the following command:

``` bash
./cub3D path_to_map_file.cub
```

Then, you can explore the 3D world using the specified controls:

- WASD keys: move forward, backward, left, and right.
- Arrow keys: Rotate the player's view left and right.
- ESC key: Exit the game.

---
Made by [dardangerguri](https://github.com/dardangerguri) and [jhesso](https://github.com/jhesso).
