Sprint 3 Report
Prepared by All Members.

## Game Engine

### Progress Reflection
Last sprint's goal of porting initial functionality into a structured codebase allowed tasks to be worked on a bit more independently. This allowed the group to work on a wider range of tasks, each dealing with different aspects of the game. During the sprint, some initial work was done on creating enemies. A* pathfinding for enemy movement was implemented, although its functionality is somewhat limited and will require a good deal of fine-tuning. Pixelation of sprites was implemented, giving the game a more cohesive look and feel. Portals, which allow the hero to move between the different game worlds, have also been implemented. A system for using configuration files to set game assets was added, making the work of adding and testing game assets much easier. In all, a good assortment of features were added during this sprint, bringing us close to the point of having the features we need for a fully-functioning game. 

### Problems Encountered
New features such as pixelating the hero and items proved to be difficult since some of the sprite class had to be re-implemented to account for the varying pixelation levels. Although the changes themselves didn't account for the largest difficulty, changing all methods which incorrectly accessed the sprite images was slightly time consuming. Additionally, the implementation of a config file, although beneficial, was also time consuming as well since objects such as the hero and portals which were previously hard coded, needed to be implemented into the config file.

### Projected Progress
With the final sprint coming up, we plan to add as many additional features as we can, but we recognize that we may not get to them all in time.  We plan on finishing the configuration file so that items and enemies are pulled from the configuration file as well.  Another priority of the upcoming sprint is to give enemies the ability to push the hero around; this is needed for some of the level designs that the game design team wishes to implement.

Other than these items, there are several other items we would like to implement, if time. The first of these is to give the items different special abilities, as determined by the game design team.  We will also be working on additional enemy A.I.s.  The game design team would also like to create a world that uses a completely different pixelation algorithm, which they call "Little-Big World".  In this world, the world will get bigger around the hero instead of decreasing resolution. This requires some fundamental changes to the way the code is designed, so we may not be able to create it in time.  Also, if time allows, we will add music and sound effects.

## Game Design

### Progress Reflection
We have completed the design of the six items in the game: eggs, milk, flour, butter, baking powder, and sugar. Furthermore, we have nearly completed the design of four of the five levels of the game.

### Problems Encountered
Many of our problems lie in the changes made by the Game Engine team. For example, the main character now can rotate and pixilates as well. While this is functionality that we want, it changes the final design of the levels since we must ensure that the user can fit through all desired openings and cannot through others. This means that we need to go back and tweak some of the levels to allow for this new functionality.

### Projected Progress
During the final sprint, we will finalize the design of all levels and create the final level. We also plan to design and implement more enemy types to incorporate into the different levels. In conjunction with the Game Engine Team, we will use the newly created config file to help us define each of the levels, the placement of items, the placement of portals and where the portals take you, and the implementation of different enemies.

## Burn Down Chart
An updated version of our burndown chart can be seen here:
https://docs.google.com/a/mail.gvsu.edu/spreadsheets/d/1uitcA24i01bWN-nSk-oQuyQdOlVkBoMgaBmvMvjDXoA/edit#gid=0

## Conclusion
At the conclusion of this project, we will have a small playable game demo, possibly with sound. With features such as pixelation, pixel perfect collision, pathfinding, and big-little world, we feel pretty happy about our game, though it might not quit be commercial grade.
