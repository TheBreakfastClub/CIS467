CIS467 - Computer Science Capstone
==================================
Grand Valley State University, Fall 2014
----------------------------------------

This repo holds the Breakfast Club's project for CIS 467 - Computer Science Capstone.

Introduction
------------

When 2D games were first created, developers/designers worried about hardware constraints. Indeed, many features of games during this era required clever strategies and methods for squeezing every bit of performance out of whatever given platform the game was to be run on. The minutia of direct hardware access, manual memory management, and so on were managed by the game programmer. Given the computing hardware of today, one would be hard-pressed to truly test hardware limits in two dimensions. Now, game programming libraries and engines run on top of sophisticated operating systems that manage these aspects, shifting the focus of the typical game programmer almost entirely on the mechanics of the game itself. The evolution of computer hardware and the software running on them has also given rise to more powerful development environments which a game producer can leverage. A 2D game created today can take advantage of preexisting libraries, sophisticated AI, high-resolution graphics, and much more.

This project attempts to take advantage of modern computer hardware and software in order to demonstrate that a 2D game of moderate complexity can be created in one semester by a small team of programmers with relatively little game programming experience. We plan to create a puzzle-based game in which the solution lies in changing the screen resolution. Players will be able to move from one area to another, gain more abilities, and defeat enemies using their power to change the resolution. To do so, we will also be creating our own game engine. Provided that there is time, enemies will be added randomly and given some basic AI to help add complexity to the gameplay.

Areas of Technical Innovation
-----------------------------
Our project aims to use the knowledge we have accumulated while attaining our Computer Science degrees at Grand Valley to create a professional and well designed product.  However, we also will be investigating several areas which we have limited or no prior experience with; this way we will push ourselves to grow, show our ability to self-learn, and gain new tools for our programming tool belts.  These research topics are our areas of *technical innovation*, and they are as follows:

### - Video Game Development

We will develop a single player, 2-dimensional, top-down action, adventure game in the style of the the classic Zelda series. 

The game engine will be written in C++ using <a href=http://www.libsdl.org>SDL 2.0</a> for audio, video, and input. Rendering will most likely all be done in software, using SDL simply to blit frames to the screen, though we may end up using openGL if we decide to implement rotation and/or scaling. Although we are only targetting Linux directly, the game engine itself will be quite portable.

Game maps will most likely be tile based, though we may experiment with large, image based maps as well. Game sprites and tiles will be drawn by hand, perhaps through Photoshop or the like. Tile based maps will be authored manually with an editor of our making, while image based maps may be created in Photoshop or generated algorithmically. We may experiment with, but not rely on, automatic map generation.

Pixel perfect collision detection may be implemented, with physical properties determined directly by pixel color and opacity.

### - Variable Detail World: Creating a Multi-Resolution Interface

When designing a video game, the graphics used in the game can be highly important to the player.  Some prefer high resolution, well-crafted graphics while others prefer a more simplified and pixelated game world, creating a retro feel that imitates the low resolution screens used during the genesis of 2D games.  For this project, we will be investigating an innovative new approach: rather than make a game in only low resolution or only in high resolution, we will create a game that experiments with changing the resolution throughout the game. Changing the resolution of the game world will change the level of detail in which the world is presented to the player.  In this way, the user would begin the game in a highly pixelated, low resolution world. However, as the player progresses, they gain the ability to increase the resolution of the world around them or to decrease it back to the original resolution.

This ability allows the player to pixelate or refine the world around them at will, with collision detection based on currently visible details. We plan to only create the highest resolution world by hand and develop a pixelation algorithm to create the lower resolution worlds from there. Pixelation may be implemented by several different algorithms, such as taking the average tile type within a region, point sampling, mean or median color, min/max for each primary color, and so on. The algorithm's default behaviour may also be overridden at times for special circumstances; for instance, certain colors or opacities in tiles or enemy sprites may be used to tell the algorithm to pixelate in a unique way.

Because of the ability to change resolutions, the player may open or block paths on the map based on the current detail level. When increasing resolution, the player may find that what they thought was a solid wall actually contains a small door.  When decreasing resolution, the player sees the logs in a river fade into a pixelated bridge. Enemies might do different amounts of damage depending on their detail level or operate under different levels of intelligence.

We do not yet know how many detail levels are desirable. We can devise cases where any number of detail levels are useful using point sampled pixelation, but this may prove too unpredictable and frustrating in practice. We would like to develop game dynamics which favor several levels of detail.


### - Artificial Intelligence

The presence of enemies within a video game necessitates giving these enemies some sort of artificial intelligence.  We plan to research and implement different well-known artificial intelligence algorithms and also to create some of our own.  We may also implement machine learning algorithms, such as genetic algorithms or neural networks.  However, we plan to implement A.I. rather late in our development cycle, and we are well aware that due to the scope of this project, we may only have time to implement basic A.I. algorithms.  If this is the case, the game may become more of a puzzle game than anything else. A.I. need not be written in C++; we may interface other languages with the game engine.

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

> 1.01 Accept full responsibility for their own work.
	Each group member must take responsibility for their assigned tasks.

> 3.02. Ensure proper and achievable goals and objectives for any project on which they work or propose.
	Although our group aims to create the best project we can; we also realize that if we attempt too much we might fall short of our goals and create an undesirable product and learning experience.

> 6.01. Help develop an organizational environment favorable to acting ethically.
	The group will address either one-on-one or in meetings any ethical concerns individuals have.

> 6.08. Take responsibility for detecting, correcting, and reporting errors in software and associated documents on which they work.
	Group members will review and test each other's code for errors. It is beneficial to the team if everyone understands the current state of the project.

> 8.02. Software Engineers shall improve their ability to create safe, reliable, and useful quality software at reasonable cost and within a reasonable time. 
	We will use all resources available to create our project.

> 7.02. Assist colleagues in professional development.
	Group members should professionally review work done by other group members. Each group member will attempt to fully address all questions about their current work to better the education of others.

> 7.05. Give a fair hearing to the opinions, concerns, or complaints of a colleague.
	All opinions must be taken into account during the project to promote an equal environment.

> 8.09. Recognize that personal violations of this Code are inconsistent with being a professional software engineer.
	Group members understand that not following the code of ethics is unprofessional and will be conscious of the code while working.



-----------------------------
_Info on TheBreakfastClub's Waffle icon:_
<i>Waffle designed by <a href="http://www.thenounproject.com/jacob">Jacob Halton</a> from the <a href="http://www.thenounproject.com">Noun Project</a></i>
