Feasibility Study
================

Software Languages and Libraries
--------------------------------
- We are developing this game for Linux in C++ 11, using the [Simple Direct Media Layer 2.0](http://www.libsdl.org) to handle graphics, audio, and input.  The STL of C++ will be used in this project.  No other libraries should be needed for this project.
- A basic program using C++ 11 and SDL 2.0 has been created and run on the EOS machines, verifying that this will be a feasible platform for developing our game.

Technical Cruxes: The Non-Trivial Requirements
-----------------------------------------------
### *Creating the Game Engine*: 
The game engine is responsible for maintaining all of the information about the game world--including the environment details (e.g where walls, trees, and rivers are located), the characters (both the hero and the enemies), and the items--and for handling interactions between these items.  The game engine must handle basic physics, such as collision detection and character/object interaction, while holding the information needed for graphics and audio. The engine will provide an API by which characters (human or A.I.) may query and interact with the game world. Characters may query the proximity of nearby enemies, objects, and obstacles.

We have considered many different ways to implement the game engine and have not yet settled on an approach. The game world's environment may be defined through pixels alone with colors indicating what the pixels represent or it may be created on a tile based system, each type of tile representing a different aspect in the environment. Collision detection will probably be implemented with bounding boxes but may also be implemented with pixel perfect collision detection. Other items will interact with the game world through either specific queries to the engine (e.g. the hero requesting whether it can move north or not) or through asking for a representation of the entire game world (such as for an enemy's A.I. to determine the enemy's next move).

### *Pixelation Algorithms*: 
The pixelation aspect of the game is one of the single most important parts of the project. It is the primary way in which the user will interact with the world and is the central aspect of gameplay. In our previous meetings, much of the conversation has revolved around the pixelation. We have decided to only create the highest resolution world and to create a pixelation algorithm to create the lower resolution worlds from the high res world.  We have discussed several possible algorithms to pixelate. Color based algorithms may be implemented which take into account the exact RGB values of the pixels within a square to de-resolve, such as taking the average of the RGB values or choosing the max, min or mean value in the set. Tile based algorithms may also be used, taking the average tile type within the square, possibly giving preference to certain types of tiles.  This part will evolve over the course of the project as we perform tests and have more conversations.  However, the design of the game world is highly coupled with the pixelation algorithm (e.g. whether it is a pixel or tile based world), so a preliminary decision will have to be made soon. 

### *Gameplay*:
The basic dynamics of the gameplay are of obvious importance to this project.  As mentioned above and in the prospectus, pixelation dynamics are of prime importance to gameplay, creating a puzzle style game. We will make it a top-down game in the style of the old Zelda games. Much of the rest of the gameplay will be determined dynamically by the team as the project develops.

Because the game needs to be developed in such a way that the gameplay can be dynamic, we will be writing our code in a very modular way. We will develop an API for each module (e.g. game engine) that is flexible and allows other modules to use it easily. We will put some thought into how this API is developed from the beginning, making sure that it allows for the various pieces of gameplay that we already know we want to add.

### *Visual Grammar*: 
An important aspect of the game is how it looks. In regards to the class, it might not seem like one of the requirements. However, the way the game looks, especially with the pixelation algorithm, determines how the game and code will be written. For example, the graphics that can be created are determined by how the game engine sees the world, based on tiles or pixels.  We have started to test ways to visualize the different possible pixelation algorithms with a simple Javascript web app. Creating small applications to test the various algorithms are a primary way to determine which approach to use because they allow us to see what each algorithm will actually look like. The other aspect of the visual grammar is just simple how it looks. We have discussed working with a more realistic game with things like grass, water and humanoid characters. We have also discussed more abstract visuals like levels, aspects of levels and characters based on colors or shapes. 

### *Artificial Intelligence (A.I.)*:
Enemy A.I. will interact with the game engine to learn about the world and choose how to act. Computer characters interact with the game engine via it's API in a manner orthogonal the manner by which the human player interacts with the game. For example, an A.I. character may query the state of it's surroundings up to the the same distance that a human player would see on their screen. A.I. modules may be written in languages other than C++ if we provide glue by which to do so. We may also implement machine learning algorithms rather than explicit A.I. for game characters (time allowing). However, A.I. will be one of the last items implemented, so only basic A.I. may be created.

Division of Labor
------------------

The work to be performed by our group will be divided up into three divisions. This division of work is to be performed by subgroups of our team members. The three divisions are *game engine*, *game design* and *game mechanics*. The *game engine* group will focus on developing the graphics implementation, character collision detection, and the overall game control. The *game design* group will focus on determining the visual appearance of the game. Lastly, the *game mechanics* group will focus on determining how the game should be played, who the hero and enemies are, how they are to behave, and what the story line of the game will consist of. 


The subgroups contain the team members that have experience or are interested in the work to be done. All team members will be a part of the *game mechanics* group as this will involve making many important decisions about the game. The *game design* group contains Thomas Verstraete and Michelle Dowling. Thomas Verstraete has a previous degree in Art and Design and an interest in how the game looks. Michelle Dowling plans to go to grad school for Human Factors and Ergonomics, making the visuals and related game concepts a particular interest to her. Colin Uhen is interested in creating music for the game and will thus also contribute to the design group. Steve Hoffman, Colin Uhen, Tashi Reigle and Tyler Hutek will work in the *game engine* group. Steven Hoffman will be part of this group because he has a particular interest in designing algorithms and working on low-level code. Tyler Hutek has worked with game AI previously and is interested in developing a game engine. Colin Uhen fits into this group due to his previous experience with several different game engines and libraries including SDL. **[??? need to fill in for individuals ???]**. Each group will work out how they wish to distribute and perform the tasks, likely distributing them to team members as the project moves forward.


One aspect that we agreed to is to have weekly, in-person meetings as a whole team and also as subgroups. In the subgroup meetings we are going to discuss what needs to be done and also what we have done. The purpose of discussing what we have done is so that all of us are able to understand the whole project. This class is meant to further our education, and if we go off on our own and don't report, then we do not all learn. We are hoping that through discussing the work we have done as we do it, all the team members may learn from each other, even in areas of the project that we have not worked ourselves.

Policy for Git
---------------
The team has chosen to integrate the project with GitHub. Each member will contribute to the master branch in the GitHub repo only once the code has been well-tested, passes all tests, and everything functions as expected. Until that state has been achieved, new code will be written in separate branches. The branches will correspond to specific new features or tasks. Once the new feature has been implemented, the individual should pull from master and bring the most current code into the branch. All conflicts should be resolved and all tests passing before integrating the branch with master and pushing to the GitHub repository. At this time, the branch may also be deleted. This way, the master branch always has the latest green, working code that everyone can use and reference. It also will help to keep the repository clean by deleting branches once they are no longer in use. How each member chooses to use the branches created (beyond these instructions) will be up to the individual or the group that is working on any given feature. No member will be permitted to change code in a branch or delete a branch that he/she is not working with directly. 

Integration of work is expected to occur as soon as new features have been added and tested, with some flexibility.  Each team member should strive to have as much of their code tested and integrated into the main branch as possible by the onset of each new Sprint.



Burndown Chart
--------------
Our burndown chart is implemented with an online collaborative spreadsheet that can be viewed [here](https://docs.google.com/spreadsheets/d/1uitcA24i01bWN-nSk-oQuyQdOlVkBoMgaBmvMvjDXoA/edit?usp=sharing). 

We used a point system to rank each task where each point approximates to about four person hours of work.
