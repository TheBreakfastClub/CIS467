# Pixel Game Manifesto

### This is the game's manifesto. All ideas should be input here so we have a central spot it accumulate ideas, which we can all edit.

## Vocabulary
* **Resolution:** The level of pixelation the game is currently in. Currenly set to have three levels.
  * **High:** The smallest pixel size with the most fitting into the tiles.
  * **Medium:** The middle pixel size.
  * **Low:** The largest pixel size with the fewest fitting into the tiles.
* **Tile:** The containing box that holds the different sized pixels. The size of this is to be the same no matter the resolution. Characters, items and possibly the map will be made up of these tiles. Every visual element will be divisible by this set size.
* **Pixel:** The single colored box that varies in size depending on the resolution. (Is not related to the pixels on the screen).
* **Hero:** The main playable character of the game.
* **Enemy:** Duh!
* **World:** A section of the game represented by a map.
* **Sub worlds: ** Worlds off the main Hub where much of the game play happens.
* **Map:** The image of pixels that represent the current world.
* **Hub:** The central world as described in the Game Universe Section.
* **Pixelation:** The process of enlarging the pixels to a larger size using a specified algorithm to create the new larger pixel.
* **Pixalation Algorithm:** The way the pixelation is computed. Taking the highest resolution to compute the other two levels. There are to be a generic algorithm and possibly character, item, and map specific algorithms

## Overall Design Ideas
The overall design is still up in the air as we need to see what possibilies there are with the pixelation. Mainly we are waiting to see what the pixelation algorithms will do to the designs. For humenoid characters it might just blur them and make them look bad. So because of that we are thinking of taking the design into a more abstract way of thinking of characters and worlds.


## Game Universe
The game universe will consist of a central map as the hub that has access through portals to the other worlds. The sub worlds are where the puzzles will be and where the Hero will collect the items. Each world will have a different pixelation algorithm that will be used. The central hub will be designed with all three resolutions in mind. One of the Sub Worlds will be designed with the lowest resolution. One will be designed with the lowest and the middle resolution. The last two will be designed with all three levels of resolution.

The different worlds described below (currently in no particular order):
* Center Hub
  * The Hero begins the game in this level.
  * Access to sub levels through "doorways" (how they access TBD).
  * The access to the sub levels will be blocked so the Hero must go in a particular order to each sub level (How TBD).
  * Where the pixelation items are to be located
    * pixelation items are to be blocked off until Hero has what is required to access them. How they are blocked TBD.
  * Also contains the Milk and Egg items.
  * Visual Style: Temple of Time-ish
  * Pixelation Levels: low, medium, high.
  * Algorithm: Average
  * Designed By: Thomas
* Flour Level
  * level that contains the Flour item.
  * description of which TBD
  * Visual Style: TBD
  * Pixelation Levels: low & after completion medium
  * Algorithm: TBD
  * Designed by: Michelle
* Sugar Level
  * level that contains the Sugar item.
  * I want there to be a lot of shifting parts. This will have to have enemies.
  * Visual Style: Think colorful crystals.
  * Pixelation Levels: low, medium & after completion high.
  * Algorithm: Averaging
  * Designed by: Thomas
* Baking Soda Level
  * level that contains the Baking Soda item.
  * description of which TBD
  * Visual Style: TBD
  * Pixelation Levels: TBD
  * Algorithm: Zooming Algorithm.
  * Designed by: Thomas
* Butter Level
  * level that contains the Butter item.
  * description of which TBD
  * Visual Style: TBD
  * Pixelation Levels: TBD
  * Algorithm: TBD
  * Designed by: Michelle


## Map
A map will be a set of images that represent the world in the game univers, and the hero will remain in the center of the screen as the map scrolls under them. If the hero reaches an edge of the map then will move from the center to the edge so that there isn't any weird void space showing. All layers of the map are to pixelate with the same algorithm.

Attributes.
* At least two, but hopefully three images make up the map.
  * Background Layer
    * The lowest or furthest back layer
    * shows the back drop of the world.
    * no transparency
  * Collision Layer
    * Middle Layer
    * On the level of the hero and enemies.
    * uses the Alpha (transperency) aspect of RGBa colors to represent solidity of the object.
  * Foreground Layer
    * closest layer.
    * used for visual interest.
    * can hide things if needed.
    * does not affect the hero or enemies.
    * has transparency.


## Pixelation
There will be three different levels of pixelation. The three levels adds a nice high, middle and low that is easier to design to. The three levels (the actual resolutions) are to be worked out by the design group. The three levels of resolution will be constant throughout the game.

### Different Pixelation Algorithms
All algorithms will ignore invisible pixels unless stated otherwise. Not all these might be used but these are the ideas.

* **RGB average:** Just taking the average red, blue and green values for all containing pixels.
* **RGB average to Light:** Same as RGB average but weighting the lighter colors more so it whitens out.
* **RGB average to Dark:** Same as RGB average but weighting the darker colors more so it blackens out.
* **Average without Alpha:** Average only the colored spots that are not transparent.
* **RGB Most Used:** Taking the most used RGB value.
* **Zooming:** This takes the color array and just blows it up to be bigger.


## Hero
Not too much going on now with the Hero. It will be a her as there are not enough female heros in games, however you might not be able to tell when the game is being played.

### Actions
We want the hero to be able to pick up items, attack enemies, and move up down left and right.

### Design
The hero will be a triangular shape to indicate direction, with a central dot that looks like a waffle. This waffle will be an empty dot to begin with and as the player collects the six items pie slice shaped pieces of the dot will fill in.

### Health meter
The health meter is set to the low resolution with x number of hits you can take. As you upgrade to a higher resolution your hit number increases with it. Now we can also make it so that when you lower resolution your hits lower as well, so you don't want to stay in low res that long.

### Item container:
As you pick up the items an icom appears on the screen to indicate that you got them. Once you get them there is no running out. Use of the item is limited to some arbitrary rejuvenation time.


## Items
The items the hero can pick up and use are all the ingredients to make a waffle. These items will be picked up once and when you get them you can use them unlimited number of times with a set refresh time frame. Aside from the pinch of salt the basic recipe comes from http://www.foodnetwork.com/recipes/simple-waffles-from-scratch-recipe.html

#### Attributes for all items
* type - config
* world - config
* location - config
* image - config
* Based on world
    * pixelation algorithm
    * pixelation resolution

### Main Items
* **Butter**
  * Makes hero move fast but makes her run like on ice.
  * Rejuvenation Time: TBD
  * Pick up Order: TBD
  * Key Command: TBD
  * World Location: Butter World
* **Suger**
  * Makes hero run fast but a straight shot in one direction
  * Rejuvenation Time: TBD
  * Pick up Order: TBD
  * Key Command: TBD
  * World Location: Sugar World
* **Flour**
  * Throwing item, when it hits the enemy it makes them transparent similar to a ghost. They can not hurt you. Lasts for a specified duration.
  * Rejuvenation Time: TBD
  * Pick up Order: TBD
  * Key Command: TBD
  * World Location: Flour World
* **Baking Powder**
  * Makes Hero transparent like a ghost. You can not get hurt by enemies and can pass through obsticals.
  * Rejuvenation Time: TBD
  * Pick up Order: TBD
  * Key Command: TBD
  * World Location: Baking Powder World
* **Eggs**
  * Throwing item, primary weapon. Just hits enemies and hurts them. Possible upgrade items to be different kinds of eggs.
  * Rejuvenation Time: TBD
  * Pick up Order: TBD
  * Key Command: TBD
  * World Location: Hub World
* **Milk**
  * Healing item. Possible upgrades to organic milk for better healing, or use the percents to have different levels of healing.
  * Rejuvenation Time: TBD
  * Pick up Order: TBD
  * Key Command: TBD
  * World Location: Hub World

### Pixelation Items
The pixelation leveling up will be done when the Hero collects the pixelation item for that resolution. The visual look of that item will be a varient on how the hero will look at that level of resolution. I was thinking that they could be grayed out versions of hero like a statue. When the Hero goes up to the item it changes or something...TBD.

### Portals
Portals are the way the hero travels between the different worlds. These are linked pairs that allow the hero to travel in both directions. There will be multiple game design determined locations within any world.

## Enemies
There will be different types of enemies. The definition of the enemies should be thought if in all three resolutions.

#### Attributes for all enemies
* world - config
* start location - config
* images - config
* Based on world
    * pixelation algorithm
    * pixelation resolution

### Enemies
* **Spiky Ball:**
  * Design: A round enemy with spikes on the outside
  * World Location: TBD
  * Pixelation Algorithm: TBD
  * High Res: The spikes will be nicely defined and will hurt the Hero when it hits her.
  * Medium Res: The spikes will blur our and will have a soft edge look. This makes the hero bounce off it and the hero can not hurt it.
  * Low Res: the spikes will now blur out completely. The hero can not attack and destroy it.


* **Ice Water Cloud:** This enemy will take on the different properties of water as it is in the different resolutions.
  * Design: an amorphous shaped blue guy
  * World Location: TBD
  * Pixelation Algorithm: TBD
  * High Res: It is a cloud and the hero is not hurt by and can not hurt it.
  * Medium Res: It is water and the hero can hurt it. But it can surround the hero and is surrounded too long it will drown the hero.
  * Low Res: It is ice. If it hits the hero it will freeze her. But can be broken apart easily.


* **Gnats:** small enemies
  * Design: a small block or circle that is capable of small amounts of damage
  * World Location: TBD
  * Pixelation Algorithm: TBD
  * High Res: The gnat is well-defined and is can harm the user
  * Medium Res: ?
  * Low Res: The gnat has been blurred out to the point that it no longer exists


* **Worm Snake:** snake-like enemy
  * Design: a cylindrical enemy that slithers through the terrain
  * World Location: TBD
  * Pixelation Algorithm: TBD
  * High Res: a large snake capable of doing a lot of damage
  * Medium Res: a smaller snale capable of doing some damage
  * Low Res: a worm that is merely a nuisance (may cause some damage)


* **Dragon:** a large, fire-breathing dragon!! (or some other large enemy)
  * Design: a red dragon capable of breathing fire. Eggs have no effect.
  * World Location: TBD
  * Pixelation Algorithm: TBD
  * High Res: a detailed dragon capable of doing large amounts of damage
  * Medium Res: a burred block that can still spread fire or otherwise do large amounts of damage. It is still impervious to eggs.
  * Low Res: a solid block that stomps around trying to hurt the user, but is now succeptable to attacks


* **Empy Box:** an empty box that tries to trap the user and prevent him/her from changing resolutions
  * Design: a blank box (nothing inside) with one side of the box left open. The box would rotate and try to trap the user within the box.
  * World Location: TBD
  * Pixelation Algorithm: TBD
  * High Res: the box is open along the one side
  * Medium Res: the box is still open, but becoming very constricting. The box may give damage if the user is inside at this point.
  * Low Res: The box is solid and has no opening

* **Obsicles:** These are verious elements in the world that are just in the way. There will be no damage enflicted on the hero if hit.
  * Design: Level dependent.
  * Level Location: All the levels
  * Pixelation Algorithm: Level dependent.

## Game Story Line

The game play begins in the central hub world. It shows the three pixelation items. The lowest pixelation item comes to life and that is your character. You explore the world to find the egg item. Then you go into the first world to get the second item. After you come back with the second item the second pixelation item is able to be accessed. You go up to it and move over/under it and then you now have the second pixelation level. You then are able to get to a part of the central hub that has the milk. Then you go to the second sub world and collect the fourth item. When the hero makes it back to the central hub then they can access the Third pixelation item. Then the hero goes to the third and fourth sub worlds to get the remaining items. After all the items are collected...something, something...the end.
