![jlug logo](https://github.com/jirouette/jlug/raw/master/res/images/logo.png "jlug") jlug
=================



What is *jlug* ?
-----------------

jlug is a *Pokémon* game base project which tries to look like old Nintendo DS *Pokemon* game such as *Pokémon version Diamond/Pearl/Platinum/HeartGold/SoulSilver* (and not *Black/White*).
It manages to display 3D map (thanks to OpenGL), with an XML-format based on *TMX Tile Mapping* format.


How to compile it
-------------------

Download the entire project by

`git clone git@github.com:jirouette/jlug.git`

then, simply do

`make`

The executable lies in __bin/__.

`bin/jlug` or `make run`


__Important :__ You'll need those different packages :

* libsfml-dev
* libtinyxml-dev
* mesa-common-dev
* freeglut3-dev
* lua5.2
* liblua5.2-0
* liblua5.2-dev

