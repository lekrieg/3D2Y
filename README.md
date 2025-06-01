# 3D2Y basic game enine

- [General explanation](#general-explanation)
- [Basics](#basics)

## General explanation
This is a game engine based on the engine from COMP4300 course from [Dave Churchill](https://www.youtube.com/@DaveChurchill/playlists).

The main idea is to be a practical tool without a lot of unnecessary windows and stuff, just open the editor, make your scenes and program the game.
The engine is built using ECS to simplify entity creation, SFML for graphics and a basic phisics (box2D will be used later on) and the folder structure was taken from GDC (game coding complete) book, it's purpose is to separate everything in its own thing.

Basically we have:

---
**Assets**: it holds the assets for the project, so designers can just throw their stuff there and people can use it.

**Docs**: used to hold the project documentations (GDD, pitch and so on).

**Engine Editor**: used to hold the engine editor so you create your levels freely.

**Game**: Holds the game itself,  the scenes and everything the game needs to run. The idea is that you can just
zip this folder and share with other people whenever you want.

**Source**: here lies all the code for the projects.

**Source/Core**: Inside this folder you have the third libraries you project needs and so on, and the source code for the engine itself.

**Source/Editor**: Inside this folder you have the code for the level editor itself.

**Source/Game**: Inside this folder you have the code for the game.

**Source/Lib/platform_stuff**: When you compile, the libs are copied from the 3rdParty folder for linking them on the project later on.

**Source/Temp/platform_stuff**: This is where you can throw your temp files so you can do a clean build whenever you want.

**Tools**: You can put useful tools there so the team can use them.

- Assets
- Docs
- Engine editor
- Game
- Source
  - Core
    - 3rdParty stuff
    - src
  - Editor
    - src
  - Game
    - Scenes
    - and so on...
  - Lib
    - platform stuff
  - Temp
    - platform stuff
- Tools
---

You can use cmake or recreate the project using premake5 and build using make or any other option premake5 gives you.

## Basics

This is the basic UML for a basic workflow with the engine:

- [ ] WIP