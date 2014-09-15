Feasabilty Study
----------------
----------------

Software Languages and Libraries
--------------------------------
- We are developing this game for Linux in C++ 11, using the [Simple Direct Media Layer 2.0](http://www.libsdl.org) to handle graphics, audio, and input.

Non-Trivial Requirements
------------------------
- Program Structure: 
The game engine is responsible for collision detection, character/object interaction, graphics, and audio. The engine provides an API by which characters (human or A.I.) may query and interact with the game world. Characters may query the proximity of nearby enemies, objects, and obstacles. They may also query the game map by location within a certain distance of their current location.
- Pixelation Algorithms: 
The pixelation aspect of the game is one of the single most important part of the project. It is the central part that the user will interact with and is the central aspect of gameplay. In our many meetings much of the conversation revolves around this part. We have discussed the algorithm to pixelate the colors and the collisions. We have discussed visual ques to inform the user of how things will pixelate before they choose to. We have discussed averaging out the red, blue and green values or choosing the max, min or mean value in the set. This part will evolve over the course of the project as we perform tests and have more conversations. 
- Game Play:
Specifics of gameplay are yet to be determined, but will be based *very* loosely on the Zelda series of games. As mentioned above, pixelation dynamics are of prime importance to gameplay.
- Visual Grammar: 
One of the important aspects of the game is how it looks. In regards to the class it might not seem like one of the requirements. However, the way the game looks, especially with the pixelation algorithm, determines how the game and code will be written. We have started to test ways to visualize the different possible algorithms with a simple Javascript web app. This is a preliminary way to look and test. The other aspect of the visual grammar is just simple how it looks. We have discussed working with a more realistic game with things like grass, water and humanoid characters. We have also discussed more abstract visuals like levels, aspects of levels and charactors based on colors or shapes. 
- A.I.:
Computer characters interact with the game engine via it's API in a manner orthogonal the manner by which the human player interacts with the game. For example, an A.I. character may query the state of it's surroundings up the the same distance that a human player would see on their screen. A.I. modules may be written in languages other than C++ if we provide glue by which to do so. We may also implement machine learning algorithms rather than explicit A.I. for game characters (time allowing).

Work Policy
-----------

The work to be performed by our group will be divided up into three divisions. This division of work is to be performed by subgroups of our team members. The three divisions are game engine, game design and game mechanics. The game engine will consist of developing the graphics implementation, character collision detection, and the overall game control. Game design includes determining the visual appearance of the game. Lastly, game mechanics is how the game is played, who the hero and enemies are and how they are to behave. 
The subgroups contain the team members that have experience or are interested in the work to be done. All team members will be a part of the game mechanics group as this will contain the most decisions about the game. The game design group contains Thomas Verstraete and Michelle Dowling. Thomas Verstraete has a previous degree in Art and Design and an interest in how the game looks. [??? Michelle needs to fill in this part ???]. Colin Uhen is interested in doing the music as a part of the game and is a small part of the design group. The remaining members of the team, Steve Hoffman, Colin Uhen, Tashi Reigle and Tyler Hutek, will work on the game engine. Tyler Hutek has worked with game AI previously and is interested in developing a game engine. [??? need to fill in for individuals ???]. The groups will work out how they wish to organize and perform the tasks. 
The one aspect that we agreed to is to have weekly in-person meetings as a whole team and subgroups. In the subgroup meetings we are going to discuss what needs to be done and also what we have done. The purpose of discussing what we have done is so that all of us are able to understand the whole project. The class is meant to further our education and if we go off on our own and don't report then only the one person learns. We are hoping to give all of us the experience of all members of the team. 
The team has chosen to integrate the project with GitHub. Each member will contribute to the master branch in the GitHub repo only once the code has been well-tested, passes all tests, and everything functions as expected. Until that state has been achieved, new code will be written in separate branches. The branches will correspond to specific new features or tasks. Once the new feature has been implemented, the individual should pull from master and bring the most current code into the branch. All conflicts should be resolved and all tests passing before integrating the branch with master and pushing to the GitHub repository. At this time, the branch may also be deleted. This way, the master branch always has the latest green, working code that everyone can use and reference. It also will help to keep the repository clean by deleting branches once they are no longer in use. How each member chooses to use the branches created (beyond these instructions) will be up to the individual or the group that is working on any given feature. No member will be permitted to change code in a branch or delete a branch that he/she is not working with directly.




Burndown Chart
--------------
Our burndown chart is implemented with an online collaberative spreadsheet that can be viewed [here](https://docs.google.com/spreadsheets/d/1uitcA24i01bWN-nSk-oQuyQdOlVkBoMgaBmvMvjDXoA/edit?usp=sharing). 

- divisions
	- engine (Tashi, Colin)
	- design (Thomas, michelle)
	- mechanical (Tyler)
Think about how many points a week we can work.
