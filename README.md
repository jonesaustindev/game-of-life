# Game of Life

Taking a go at [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) with C using [Raylib](https://www.raylib.com/).

I'm sure there are more elegant ways to go about it, but it was fun to think through.



https://github.com/user-attachments/assets/f79ed730-0eaa-473e-a036-7dd4e793cc97



## Running the game
If you are wanting to run this locally, you can follow these steps after cloning the repo:

### Download a binary release of Raylib
Go to a release page for any Raylib version, though I specifically used [v5.5 of Raylib](https://github.com/raysan5/raylib/releases/tag/5.5) for this.

After downloading the binary, unzip the folder and place it in the root of the project.
```bash
raylib-5.5_macos/ # or whichever platform you are using
```

### Update the Makefile if needed
If you are not using MacOS, you will need to update the Makefile a bit to work with your OS. Mainly updating where the include and lib folders are, and the linked libs.

### Running the game
Once you have everything setup, in the root directory run:
```bash
make run
```

### Developing
If you want to play around with the code, you can run `cleanrun` to recompile and run the game:
```
make cleanrun
```

If you want to generate compile_commands.json for `clangd`, I used [bear](https://github.com/rizsotto/Bear) and found it easy enough to use.

After installing `bear`, in the root directory run:
```bash
bear -- make
```
