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
* **Map:** The set of tiles or pixels that represent the current level
* **Pixelation:** The process of enlarging the pixels to a larger size using a specified algorithm to create the new larger pixel.
* **Pixalation Algorithm:** The way the pixelation is computed. Taking the highest resolution to compute the other two levels. There are to be a generic algorithm and possibly character, item, and map specific algorithms

## Overall Design Ideas
The overall design is still up in the air as we need to see what possibilies there are with the pixelation. Mainly we are waiting to see what the pixelation algorithms will do to the designs. For humeniod characters it might just blur them and make them look bad. So because of that we are thinking of taking the design into a more abstract way of thinking of characters and worlds.


## Map
The map will be a large set of tiles or pixels, and the hero will remain in the center of the screen as the map scrolls under them. If the hero reaches an edge of the map then will move from the center to the edge so that there isn't any weird void space showing.

The map will have to be predefined by us. There might possibly be many maps for the different levels. However at first there will be just one.

### Map Tile Types
* **Glass Windows:** as the name suggests. This is able to section off areas before the user is upgraded.
  * High Res: it is glass and can be broken through
  * Medium Res: plexy glass can be broken with effort
  * Low Res: steel, can not be broken through.


* **Barred Windows:** This is able to section off areas after the user is upgraded.
  * High Res: the bars are fully defined, blocking any passage
  * Medium Res: ?
  * Low Res: bars have been blurred out to the point that the user can pass through

## Pixelation
The current idea is that there will be three different levels of pixelation. This is a somewhat arbitrary constraint do to time, however the three levels adds a nice high, middle and low that is easier to design to. The three levels are to be worked out by the design group.

### Different Pixelation Algorithms
All algorithms will ignore invisible pixels unless stated otherwise. Not all these might be used but these are the ideas.

* **RGB average:** Just taking the average red, blue and green values for all containing pixels.
* **RGB average to Light:** Same as RGB average but weighting the lighter colors more so it whitens out.
* **RGB average to Dark:** Same as RGB average but weighting the darker colors more so it blackens out.
* **RGB Most Used:** Taking the most used RGB value.


## Hero
Not too much going on now with the Hero. It will be a her as there are not enough female heros in games, however you might be ever be able to tell when the game is being played.

### Actions
We want the hero to be able to pick up items, attack enemies, and move up down left and right

### Design
The hero will be top down view so if it is a humeniod you will just see their head.

The health meter is set to the low resolution with x number of hits you can take. As you upgrade to a higher resolution your hit number increases with it. Now we can also make it so that when you lower resolution you hits lower as well, so you don't want to stay in low res that long.

### Item container:
you are given a grid of slots you can put items. As you pick up things you place the items in the grid. and removing them as you use them. When you upgrade to a higher resolution you grid changes to be able to hold more stuff. So each item takes up one pixel but you have more pixel slots to put things in. Idea to also have the different items take up a different number of pixels.


## Items
The items the hero can pick up and use are all the ingredients to make a waffle. Not sure if they will be laying around and you pick them up with a limited number of uses or if these there is only one of each and you have an infinite (but limited) number of uses.
* **Butter:** Makes hero run fast but makes her run like on ice.
* **Suger:** Make hero run fast but a straight shot in one direction
* **Flour:** Throwing item, when it hits the enemy it makes them transparent similar to a ghost. They can not hurt you. Lasts for a specified duration.
* **Baking Soda:** Makes Hero transparent like a ghost. You can not get hurt by enemies and can pass through obsticals.
* **Eggs:** Throwing item, primary weapon. Just hits enemies and hurts them. Possible upgrade items to be different kinds of eggs.
* **Milk:** Healing item. Possible upgrades to organic milk for better healing, or use the percents to have different levels of healing.



## Enemies
There will be different types of enemies. The definition of the enemies should be thought if in all three resolutions.

### Enemies
* **Spiky Ball:**
  * Design: A round enemy with spikes on the outside
  * High Res: The spikes will be nicely defined and will hurt the Hero when it hits her.
  * Medium Res: The spikes will blur our and will have a soft edge look. This makes the hero bounce off it and the hero can not hurt it.
  * Low Res: the spikes will now blur out completely. The hero can not attack and destroy it.


* **Ice Water Cloud:** This enemy will take on the different properties of water as it is in the different resolutions.
  * Design: an amorphous shaped blue guy
  * High Res: It is a cloud and the hero is not hurt by and can not hurt it.
  * Medium Res: It is water and the hero can hurt it. But it can surround the hero and is surrounded too long it will drown the hero.
  * Low Res: It is ice. If it hits the hero it will freeze her. But can be broken apart easily.


* **Gnats:** small enemies
  * Design: a small block or circle that is capable of small amounts of damage
  * High Res: The gnat is well-defined and is can harm the user
  * Medium Res: ?
  * Low Res: The gnat has been blurred out to the point that it no longer exists


* **Worm Snake:** snake-like enemy
  * Design: a cylindrical enemy that slithers through the terrain
  * High Res: a large snake capable of doing a lot of damage
  * Medium Res: a smaller snale capable of doing some damage
  * Low Res: a worm that is merely a nuisance (may cause some damage)


* **Dragon:** a large, fire-breathing dragon!! (or some other large enemy)
  * Design: a red dragon capable of breathing fire. Eggs have no effect.
  * High Res: a detailed dragon capable of doing large amounts of damage
  * Medium Res: a burred block that can still spread fire or otherwise do large amounts of damage. It is still impervious to eggs.
  * Low Res: a solid block that stomps around trying to hurt the user, but is now succeptible to attacks


* **Empty Block:** an empty box that tries to hurt the user
  * Design: a white box with clearly defined borders
  * High Res: the box is filled with different colors to indicate that the box is full. The box can only move slowly, but does more damage.
  * Medium Res: The box moves more quickly and still does some damage. The interior of the box is lighter.
  * Low Res: The box is empty. While the box can move more nimbly, it is easy to destroy.
