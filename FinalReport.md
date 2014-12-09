# Final Report
Prepared by All Members.

##Abstract
Video games have become an influential part of today’s culture.  These games are often a large collection of complex and interacting components, and, because of this, the process to develop them can be quite intensive.  Our group decided to build a video game from scratch, allowing us to gain the experience of juggling the many different processes involved in video game development.

We created a top-down, two-dimensional video game. The main goal for this game is to make a waffle by collecting the six ingredients needed.  However, these items are scattered across five different worlds and different puzzles must be overcome in order to retrieve them.  To add a unique flair to our game, we decided to experiment with pixilation.  When the game is started, the user begins in a low-resolution, highly-pixilated world.  However, as the game progresses, the user gains the ability to increase the resolution of the world, and the user interacts with each resolution level differently.  In this way, we were able to create puzzles where choosing the correct resolution is the solution.

Throughout the game development, we faced many interesting and fun challenges.  In designing the game, we needed to create ways for items to interact and collide with each other, and we implemented pixel perfect collision detection to do this.  One key challenge of this project was implementing our own pixilation algorithms which could take a high resolution image and convert them to lower resolution images.  We also implemented our own path finding algorithms to improve enemy A.I. and had to make many design decisions so that the final game produced was something a user would want to play.

##Introduction
When playing a favorite video game, one does not usually think about how the game was made.  For a computer programmer, however, the large amount of complex and interacting components involved within video games can make developing a game an intriguing challenge.  As a group, we the Breakfast Club decided that we wanted to take on the challenges involved in developing a video game.   Rather than use those software development tools which can create much of a video game for you, we decided to create the game from the ground up, only using the Simple DirectMedia Layer (SDL) graphics library as an aid, which allowed us to gain direct access to the pixels on the screen.  By building our game from scratch, we would have experience creating all aspects of a video game and would have maximum control in designing the game just as we wanted.

We decided to create a 2D, top-down video game. In this game, the main goal is to collect the six ingredients needed to make a waffle—eggs, milk, butter, sugar, baking powder, and flour.  These items are scattered across five different worlds and different puzzles must be overcome in order to retrieve these items.  The primary unique feature we added to this game is pixilation.  When the game is started, the user begins in a low-resolution, highly-pixilated world.  As the game progresses, the user gains the ability to increase the resolution of the world to a medium resolution and to a high resolution.  The user is then able to interact with the world differently in these different resolutions.  For example, the high resolution world may contain skinny walls which fade away in the low resolution, creating a pathway.  Or, for example, the low resolution world may become blurry and too hard to navigate but increasing the resolution would make the pathway clearer.  In this way, puzzles are created by the varying levels of pixilation and resolution becomes the solution.

Because we created this game from the ground up, many aspects of the design had to be solidified early on in the game design phase.  For 2D games, worlds are usually defined either by using a tile based system—where the world is created by a set of repeating tiles, each with its own properties—or by using a pixel based system—where the world is completely defined by the individual pixels that make up the game map and the sprites.  To make the game play more flexible, we decided to use a pixel based system.  This design choice affected many other aspects of the game, including collision detection.  The two standard types of collision detection are bounding-box detection and pixel perfect collision detection. Because pixel perfect collision works well when using pixel based game systems, we decided to implement pixel perfect collision detection.  As we were working with the individual pixels, we created pixilation algorithms which could take a high resolution image and “pixilate” them, creating a lower resolution image.

While designing the game, we decided that it would be beneficial to add enemies into the game. However, in order to include the type of enemies that we wanted, we needed to create an artificial intelligence (A.I.) to control these enemies.  After creating a few prototype enemies with limited intelligence, we decided to implement enemies that used path finding algorithms.  The path finding algorithms we implemented allowed us to create smart enemies which could hunt down the hero, finding paths around most any obstacle in their way.

Aside from the software development, creating this game involved many purely design decisions.  For example, we needed to decide how the user was to control the hero, what the different worlds would look like, how the hero would interact with the environment, and how the game was to be won or lost.  Because these decisions affected the way the user would play and interact with the game at such a fundamental level, we decided to have two of our members devoted to making these decisions and creating the images defining the game worlds.

##Body

##Ethical Reflection

1.01 Accept full responsibility for their own work.

Throughout each sprint, every group member has successfully taken full responsibility for their work. Every member was honest and thorough with the quality of any material they submitted. This was not only helpful, but necessary during times such as midterms when there was pressure from other classes.

3.02 Ensure proper and achievable goals and objectives for any project on which they work or propose.

This was one of the more difficult principles to follow while creating our project. While each group member wanted our game to be as successful as possible, we also needed to keep in mind the time constraints for this project. Although we tried to create obtainable goals during the feasibility study of the project, some aspects such as having several unique enemies and items became too difficult to complete in one semester. This is mainly due to most group members having no previous experience in game development.

6.01 Help develop an organizational environment favorable to acting ethically.

Each group member has encouraged ethical actions throughout the semester. We planned on addressing any ethical concerns one on one, but none arose.

6.08 Take responsibility for detecting, correcting, and reporting errors in software and associated documents on which they work.

Whenever a group member pushed new code to a branch, they were honest with any errors that existed within the code. If unknown bugs were discovered, the appropriate group member was notified and took responsibility with correcting the error.

8.02 Software engineers shall improve their ability to create safe, reliable, and useful quality software at reasonable cost and within a reasonable time.

Although it would be easy to create a program in an environment which every group member is familiar with; we wanted to use this opportunity to strengthen our coding abilities. We have successfully done this with each  group member exploring new coding opportunities such as creating in game AI.

7.02 Assist colleagues in professional development.

Each group member has done exceptionally well with reviewing each other's work to help ensure the best code possible. In addition to that, each group member was very open to critiques by other members as well. 

7.05 Give a fair hearing to the opinions, concerns, or complaints of a colleague.

Each Friday the group met to discuss the status of the project as well as how to handle features within the code. During this time, all group members voiced and opinions and concerns towards and suggestions made. Even if a suggestion isn’t as good as other ones, it was still treated with the same respect as any other suggestion.

8.09 Recognize that personal violations of this code are inconsistent with being a professional software engineer.

Every group member understood that violating the code of ethics was frowned upon and unprofessional. Because of this, no group member violated the code of ethics.


#Conclusion

Although we have worked on many projects before; this capstone was a completely different experience with its size and scope. Unlike previous projects where the professor expects students to know all of the material of the project, each group member has explored new material during this time and has grown significantly. As important as learning new coding knowledge is; many valuable lessons on working in a large group for a large project were learned as well.

The most significant lesson learned was how important it is to have a clear set of requirements to meet. At the start of the semester we had grandiose ideas of what could be included in our game which seemed to change every week as more ideas were added. As the semester progressed though, it became apparent that new features needed to stop being added if we wanted to have a complete game by the end of the semester. If we would have had a meeting earlier in the semester to decide on a concrete set of features, it would have enforced the direction that the group needed to go for the game and less time would have been spent figuring out features which didn’t make it into the game.

Another significant lesson is that we needed to allow extra time for some features to take longer than expected. Although most game mechanics took roughly the time allotted to them, some mechanics such as dynamically changing the size of the hero took significantly longer than expected. If we had given some leniency for larger tasks,  it would have made the development of the game less stressful.

Finally, although we already knew this to an extent; we realized how significant communication was for this project. We met as a group at least once a week to discuss the status of the project and to divide up work among group members. We also used a service called Slack which was used to communicate between group members easily. We all agree that without this constant communication our game wouldn’t have been nearly as complete.

There were two main difficulties that were encountered during this project; the code structure having to be constantly reworked when new features were implemented, and only 2 of the 6 group members having any previous experience with game development experience.The code structure having to be reworked several times could have been avoided if we would have had decided on all game mechanics at the start of the sprint. Having the other group members explore game development was unavoidable, but wasn’t a problem once the project was started and members were able to take the time to learn how to use SDL 2.0.

Overall, this project went fairly smooth; but, there are some changes that could have been made to further smooth out the project.As stated in the lessons we learned, a main change that we would make is to take more time at the start of the sprint to decide on every game aspect so there would be less confusion on what features would be added in as the project progressed. Additionally, we believe that although meeting up once a week was key to this project’s success, it would have been even more helpful to meet more than once a week.

Although the semester has come to a close, we believe that our project can still be further expanded on. For example, we have implemented two types of enemies, but still have several other enemy types which we could add in. Additionally, more levels and item uses could still be implemented as well. Luckily, with the modularity of our code, implementing most of these features wouldn’t require a major reworking of the code.

Communication was a major factor to this project’s success; but wasn’t the only resource used to ensure our project’s success. We used a website called Slack which was used to create several personal chat rooms for the game engine, graphics, and design aspects. This allowed discussions to be organized and able to be referred back to. A GitHub repository was created as well with multiple branches to ensure that the master branch was always a properly working and presentable program. Finally, Trello was used to keep track of tasks needed for the current sprint.

Grand Valley has done a great job of preparing us for this project, but didn’t fully prepare all group members for every aspect of the project. Most group members didn’t have any previous experience with creating a graphics engine which made the start of the project slightly difficult. If a graphics course was offered more frequently more group members could have had more knowledge on the subject. Finally, although group work is encouraged in most CS courses, very few have large group work such as 4 or more students. This caused some minor trouble as we tried to determine the best method to divide up work between so many people. Although it is easy to say that our group was fairly large at 6 people, many companies will have us working with much more than 5 other people.
	
