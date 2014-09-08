CIS467 - Computer Science Capstone
==================================
Grand Valley State University, Fall 2014
----------------------------------------

This repo holds the Breakfast Club's project for CIS 467 - Computer Science Capstone.

Introduction
------------

When 2D games were first created, developers/designers worried about hardware constraints. Indeed, many features of games during this era required clever strategies and methods for squeezing every bit of performance out of whatever given platform the game was to be run on. The minutea of the hardware implementation, such as memory management, were managed by the game programmer. Given the computing hardware of today, one would be hard-pressed to truly test hardware limits in two dimensions. Now, game programming libraries and engines run on top of sophisticated operating systems that manage these aspects, shifting the focus of the programmer almost entirely on the mechanics of the game itself. The evolution of computer hardware and the software running on them has also given rise to more powerful development environments in which a game producer can leverage. A 2D game created today can take advantage of preexisting libraries, sophisticated AI, high-resolution graphics, and much more.

This project attempts to take advantage of modern computer hardware and software in order to demonstrate that a 2D game of moderate complexity can be created in one semester by a small team of programmers with relatively little game programming experience. We plan to create a puzzle-based game in which the solution lies in changing the screen resolution. Players will be able to move from one area to another, gain more abilities, and defeat enemies using their power to change the resultion. To do so, we will also be creating our own game engine. Provided that there is time, enemies will be added randomly and given some basic AI to help add complexity to the gameplay.

Areas of Technical Innovation
-----------------------------
Our project aims to use the knowledge we have accumulated throughout our Computer Science degree at Grand Valley to create a professional and well designed product.  However, we also will be investigating several areas which we have limited or no prior experience with; this way we will push ourselves to grow, show our ability to self-learn, and gain new tools for our programming tool belts.  We call these research topics our areas of *technical innovation*, and they are as follows:

### - Video Game Development

### - Pixelinator: Investigating a Multi-Resolution Interface

With the large amount of 2D video games that are in existence today, games with a large variety of screen resolutions have been developed. Many of the original video games sported low resolution, highly pixelated displays, and new games will often imitate this resolution in order to maintain the retro appeal of these original games.  However, with increases in technology, it is not uncommon to play high resolution, well crafted games with highly tuned computer graphics.

When designing this game, we decided that we would like to take an innovative new approach: rather than make a game in only low resolution or only in high resolution, we would create a game that experiments with changing the resolution throughout the game.  In this way, the user would begin the game in a highly pixelated, low resolution world.  However, as the player progresses, they gain the ability to increase the resolution of the world around them or to decrease it back to the original resolution. When increasing the resolution, the player may find that what they thought was a solid wall actually contains a small door.  When dropping resolution, the player sees the logs in a river grow into a pixelated bridge.

Creating a game with a resolution-changing engine, what we call our *Pixelinator*, will surely involve research into how it can best be implemented. At a basic level, it will likely involve an averaging algorithm which takes the high resolution tiles in a section of the screen and replaces them with the average tile type contained within in order to decrease the resolution to a larger, simpler world.  But many more items will have to be taken into consideration, and we are looking forward to creating a multi-resolution interface.

### - Artificial Intelligence

The presence of enemies within a video game necessitates giving these enemies some sort of artificial intelligence.  While many of us have had some minor exposure to the concepts of A.I. and machine learning, none of us have implemented any complex level of game A.I.  We plan to research and implement different well-known artificial intelligence algorithms and also to create some of our own in order to grow our expertise in this fascinating area of computer science and to make our game more fun to play.  We are all very excited to dive into the field of A.I.  However, we plan to implement A.I. rather late in our development cycle, and we are well aware that due to the scope of this project, we may only have time to implement basic A.I. algorithms.


Backlog
-----------------------------
1. Game Engine
	1. Basic game engine
		1. See things move
		2. Static collision detection
	2. API structure definition
2. Visual/Audio Design
	1. Visuals/pixelation
		1. Determine algorithm to pixelate
	2. Game world
		1. Design levels
	3. Sprites/items
		1. Character Design
			1. Main Character
			2. Enemies
		2. Items
			1. Main Character Items/Weapons
			2. 6 Tokens
	4. Enemy placement
	5. Music/SFX
3. Game Design
	1. Specific game mechanics 
		1. How items move
		2. How items interact
	2. Character definition
		1. Main character behavior
	3. Controls
	4. Enemy AI

8 Code of Ethics Principles
-----------------------------
After reviewing and assessing  the Software Engineering Code of Ethics and Professional Practice; we have decided on the following 8 principles are the most relevant to our project:

1.01 Accept full responsibility for their own work
	Each group member must take responsibility for their assigned tasks. For our team to work

3.02. Ensure proper and achievable goals and objectives for any project on which they work or propose.
	Although our group aims to create the best project we can; we also realize that if we attempt to much we might fall short of our goals and create an undesirable product.

6.01. Help develop an organizational environment favorable to acting ethically.
	The group environment must foster ethical principles.

6.08. Take responsibility for detecting, correcting, and reporting errors in software and associated documents on which they work.
	Group members must make have accountability for their work. It is beneficial to the team if everyone understands the current state of the project.

7.01. Encourage colleagues to adhere to this Code.
	Group members must not only follow the code of ethics, but must also encourage others to act ethically.

7.02. Assist colleagues in professional development.
	Group members should professionally review work done by other group members.
7.05. Give a fair hearing to the opinions, concerns, or complaints of a colleague.
	All opinions must be taken into account during the project to promote an equal environment.

8.09. Recognize that personal violations of this Code are inconsistent with being a professional software engineer.
	Group members will understand that not following the code of ethics is unprofessional.



-----------------------------
_Info on TheBreakfastClub's Waffle icon:_
<i>Waffle designed by <a href="http://www.thenounproject.com/jacob">Jacob Halton</a> from the <a href="http://www.thenounproject.com">Noun Project</a></i>
