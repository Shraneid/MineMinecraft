# MineMinecraft
C++ Minecraft clone that I built to learn the basics of how to create and use shaders, and computer graphics more generally.

## Example

![exampleGIF](https://github.com/Shraneid/MineMinecraft/blob/main/README.gif)

## Optimization

I started optimizing the rendering, not rendering the blocks that are hidden (that's what you see when I noclip through the ground, it is actually filled with blocks, they are just not rendered).

Right now, blocks rendering is only optimized locally on every chunk, one thing to do to improve rendering time, would be to optimize blocks/vertices between chunks which should be fairly simple to implement. 

Also, right now the chunks exist only in the Main.cpp, it should be refactored to a World.cpp class that would manage a skybox (not implemented yet), and all of the chunks, which would probably simplify world-wide optimizations while chunk-wise are handled by the chunk class.

## Terminology

* block : A block in the voxel engine
* chunk : A chunk of blocks, here 16x16x16
* skybox : A huge box that limits the player's line of sight, to allow for seemingly infinite worlds to be rendered. It moves with the player, everything outside the skybox should not be rendered (and probably not loaded, for very far objects)
* noclip : When the clipping of your character is not activated (essentially, when you can go through walls and through the ground)

## Author
* **Quentin Tourette** - *Initial Work*
