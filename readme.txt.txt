Question :

1) Have two animations for a player (run and jump) : Handling this with curson up and left right.
2) Move the parallax opp direction of the player : done
3) Have random objects move towards the player : objects are apple and bomb and are moving in towards the direction of player.
4) Make player jump over objects with jump animation : done
5) Make objects disappear if player collide : If it collides with apple, it disappears and if it collides with bomb program is exit. Wanted to create a new screen on collision to show the final score but was not able to do..


Changes : 
- Created a new class collider to calculate the collision coordinates of the objects with the player.
- DrawGLScene in GLScene.cpp function handles all the display of the player and objects which includes updating the position of player and objects (line 184-210).
