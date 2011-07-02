#include "character.hpp"

/**
* \file character.cpp
* \author JirialMovie
*/




/**
* \brief Constructor
* \param imageM : reference to the ImageManager instance.
*
* Initialisize everything to default.
*/

jlug::Character::Character(jlug::ImageManager& imageM):
                        charset(0), name(""), x(0), y(0), z(0), IM(imageM), pixX(x*16), pixY(y*16), position(jlug::Move::DOWN),
                        direction(jlug::Move::NONE), previousDirection(jlug::Move::NONE), speed(4), isMoving(false), animation(0),
                        lastAnimation(clock()), animationTime(0.2), previousAnimation(1)
{}

/**
* \brief Constructor
* \param cid : Charset ID
* \param name : Character's name. May be empty.
* \param imageM : reference to the ImageManager instance.
*
* Initialisize everything.
*/

jlug::Character::Character(unsigned int cid, const std::string& cname, jlug::ImageManager& imageM):
                        charset(cid), name(cname), x(0), y(0), z(0), IM(imageM), pixX(x*16), pixY(y*16), position(jlug::Move::DOWN),
                        direction(jlug::Move::NONE), previousDirection(jlug::Move::NONE), speed(4), isMoving(false), animation(0),
                        lastAnimation(clock()), animationTime(0.2), previousAnimation(1)
{}

/**
* \brief Constructor
* \param cid : Charset ID
* \param name : Character's name. May be empty.
* \param x : X-position of the character.
* \param y : Y-position of the character.
* \param imageM : reference to the ImageManager instance.
*
* Initialisize everything.
*/

jlug::Character::Character(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, jlug::ImageManager& imageM):
                        charset(cid), name(cname), x(posx), y(posy), z(0), IM(imageM), pixX(x*16), pixY(y*16), position(jlug::Move::DOWN),
                        direction(jlug::Move::NONE), previousDirection(jlug::Move::NONE), speed(4), isMoving(false), animation(0),
                        lastAnimation(clock()), animationTime(0.2), previousAnimation(1)
{}

/**
* \brief Constructor
* \param cid : Charset ID
* \param name : Character's name. May be empty.
* \param x : X-position of the character.
* \param y : Y-position of the character.
* \param imageM : reference to the ImageManager instance.
*
* Initialisize everything.
*/

jlug::Character::Character(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, unsigned int posz, jlug::ImageManager& imageM):
                        charset(cid), name(cname), x(posx), y(posy), z(posz), IM(imageM), pixX(x*16), pixY(y*16), position(jlug::Move::DOWN),
                        direction(jlug::Move::NONE), previousDirection(jlug::Move::NONE), speed(4), isMoving(false), animation(0),
                        lastAnimation(clock()), animationTime(0.2), previousAnimation(1)
{}



/**
* \brief Destructor
*/

jlug::Character::~Character(void)
{}

/**
* \brief set manually an X-position
* \param posx : new X-position
*/

void jlug::Character::setX(unsigned int posx)
  {
      x = posx;
      pixX = x*16;
  }

/**
* \brief set manually an Y-position
* \param posy : new Y-position
*/

void jlug::Character::setY(unsigned int posy)
 {
     y = posy;
     pixY = y*16;
 }

/**
* \brief set manually a Z-position
* \param posz : new Z-position
*/

void jlug::Character::setZ(unsigned int posz)
 {
     z = posz;
 }


/**
* \brief set manually a 2D coord
* \param posx : new X-position
* \param posy : new Y-position
*/
void jlug::Character::setCoord(unsigned int posx, unsigned int posy)
 {
     setX(posx);
     setY(posy);
 }

/**
* \brief set manually a 3D coord
* \param posx : new X-position
* \param posy : new Y-position
* \param posz : new Z-position
*/

void jlug::Character::setCoord(unsigned int posx, unsigned int posy, unsigned int posz)
 {
     setCoord(posx, posy);
     setZ(posz);
 }

/**
* \brief set manually a charset
* \param cid : new charset
*/

void jlug::Character::setCharset(unsigned int cid)
 {
     charset = cid;
 }

/**
* \brief set manually a name
* \param cname : new name
*/

void jlug::Character::setName(const std::string& cname)
 {
     name = cname;
 }

/**
* \brief set sprite position
* \param pos : new sprite position
*/

void jlug::Character::setPosition(const jlug::Move::Direction& pos)
 {
     if (pos != jlug::Move::NONE)
        position = pos;
 }

/**
* \brief set move direction
* \param dir : new move direction
*/

void jlug::Character::setDirection(const jlug::Move::Direction& dir)
 {
     if (direction != dir)
        previousDirection = direction;
     direction = dir;
 }

/**
* \brief set speed
* \param speedParam : new speed
*/

void jlug::Character::setSpeed(unsigned int speedParam)
 {
     speed = speedParam;
 }





/**
* \brief get character's X-position
* \return X-position
*/

unsigned int jlug::Character::getX(void)
 {
     return x;
 }

/**
* \brief get character's Y-position
* \return Y-position
*/

unsigned int jlug::Character::getY(void)
 {
     return y;
 }

/**
* \brief get character's Z-position
* \return Z-position
*/

unsigned int jlug::Character::getZ(void)
 {
     return z;
 }

/**
* \brief get character's 2D coord
* \return 2D coord in a Rect
*/

jlug::Rect jlug::Character::getCoord(void)
 {
     jlug::Rect coord = {x, y, 0, 0};
     return coord;
 }

/**
* \brief get character's charset
* \return charset's ID
*/

unsigned int jlug::Character::getCharset(void)
 {
     return charset;
 }

/**
* \brief get character's name
* \return name in a std::string
*/

const std::string& jlug::Character::getName(void)
 {
     return name;
 }

/**
* \brief get sprite's position
* \return sprite's position in a Move::Direction
*/

const jlug::Move::Direction& jlug::Character::getPosition(void)
 {
     return position;
 }

/**
* \brief get character's move direction
* \return character's move direction in a Move::Direction
*/

const jlug::Move::Direction& jlug::Character::getDirection(void)
 {
     return direction;
 }

/**
* \brief get character's speed
* \return character's speed
*/

unsigned int jlug::Character::getSpeed(void)
 {
     return speed;
 }




/**
* \brief check the collision in order to allow or not the character to move
* \param map : reference to the current map
*/

bool jlug::Character::checkCollisions(jlug::Map& map)
 {
     unsigned int tileWidth(map.getTileWidth()), tileHeight(map.getTileHeight());
     int nextXtile(0), nextYtile(0);//, nextSpeedXtile(0), nextSpeedYtile(0);
     int newspeed(-1);
     if (isMoving && direction != jlug::Move::NONE)
     {
         switch (direction)
         {
             case jlug::Move::LEFT:
                nextXtile = (static_cast<int>(pixX)- // minus
                                    (   (speed>tileWidth)
                                        ?static_cast<int>(speed)
                                        :static_cast<int>(tileWidth)
                                        // We use speed if the speed makes character walk several tiles in one time
                                    )
                            )/static_cast<int>(tileWidth);
                nextYtile = y;
             break;

             case jlug::Move::RIGHT:
                nextXtile = (static_cast<int>(pixX)+ // plus
                                    (   (speed>tileWidth)
                                        ?static_cast<int>(speed)
                                        :static_cast<int>(tileWidth)
                                        // We use speed if the speed makes character walk several tiles in one time
                                    )
                            )/static_cast<int>(tileWidth);
                nextYtile = y;
             break;

             case jlug::Move::DOWN:
                nextXtile = x;
                nextYtile = (static_cast<int>(pixY)+ // plus
                                    (   (speed>tileHeight)
                                        ?static_cast<int>(speed)
                                        :static_cast<int>(tileHeight)
                                        // We use speed if the speed makes character walk several tiles in one time
                                    )
                            )/static_cast<int>(tileHeight);
             break;

             case jlug::Move::UP:
                nextXtile = x;
                nextYtile = (static_cast<int>(pixY)+ // minus
                                    (   (speed>tileHeight)
                                        ?static_cast<int>(speed)
                                        :static_cast<int>(tileHeight)
                                        // We use speed if the speed makes character walk several tiles in one time
                                    )
                            )/static_cast<int>(tileHeight);
             break;

             default:
                // Nothing to do
             break;
         }
         newspeed = checkTileRow(map, z, x, y, nextXtile, nextYtile);
         if (newspeed != -1)
         {
             newspeed *= (direction == jlug::Move::LEFT || direction == jlug::Move::RIGHT) ? tileWidth : tileHeight;
             if (speed > newspeed)
                speed = newspeed;
         }
     }
     return true;
 }

/**
* \brief read a row of tile in order to check collisions
* \param map : reference to the current map
* \param tileZ : Z-position
* \param startTileX : X-position of the starting tile.
* \param startTileY : Y-position of the starting tile.
* \param endTileX : X-position of the ending tile.
* \param endTileY : Y-position of the ending tile.
* \return tiles between the starting tile and the first blocking collision occurence. -1 if there is no blocking collision.
*/
int jlug::Character::checkTileRow(jlug::Map& map, unsigned int tileZ, int startTileX, int startTileY, int endTileX, int endTileY)
 {
     if (startTileX == endTileX)
     {
         if (startTileY >= endTileY)
         {
            if (startTileY < 0)
                return 0;
            else if (endTileY < 0)
                return startTileY;
            else if (startTileY >= map.getHeight())
                return 0;
            else
                for (int i(startTileY) ; i >= endTileY ; --i)
                {
                    if (0)//map.getLayers()[tileZ].collision(startTileX, i) == jlug::WALL)
                        return startTileY-i;
                }
            return -1;
         }
        else if (startTileY <= endTileY)
        {
            if (startTileY >= map.getHeight()-1)
                return 0;
            else if (endTileY >= map.getHeight()-1)
                return map.getHeight()-1-startTileY;
            else if (endTileY < 0)
                return 0;
            else
                for (int i(startTileY) ; i <= endTileY ; ++i)
                {
                    if (0)//map.getLayers()[tileZ].collision(startTileX, i) == jlug::WALL)
                        return startTileY+i;
                }
            return -1;
        }
     }
     else if (startTileY == endTileY)
     {
         if (startTileX >= endTileX)
         {
            if (startTileX < 0)
                return 0;
            else if (endTileX < 0)
                return startTileX;
            else if (startTileX >= map.getWidth())
                return 0;
            else
                for (int i(startTileX) ; i >= endTileX ; --i)
                {
                    if (0)//map.getLayers()[tileZ].collision(i, startTileY) == jlug::WALL)
                        return startTileX-i;
                }
            return -1;
         }
        else if (startTileX <= endTileX)
        {
            if (startTileX >= map.getWidth()-1)
                return 0;
            else if (endTileX >= map.getWidth()-1)
                return map.getWidth()-1-startTileX;
            else if (endTileX < 0)
                return 0;
            else
                for (int i(startTileX) ; i <= endTileX ; ++i)
                {
                    if (0)//map.getLayers()[tileZ].collision(i, startTileY) == jlug::WALL)
                        return startTileX+i;
                }
            return -1;
        }
     }
     else // This method only checks a row of tile.
        return -1;
 }

/**
* \brief move the character
*/

void jlug::Character::move(jlug::Map& map)
 {
     unsigned int altSpeed(0);
     unsigned int tileWidth(map.getTileWidth());
     unsigned int tileHeight(map.getTileHeight());
     int pixbetween(0);

     if (checkCollisions(map))
     {
         isMoving = true;

         switch (direction)
         {
             case jlug::Move::UP:
                pixY -= speed;
             break;

             case jlug::Move::DOWN:
                pixY += speed;
             break;

             case jlug::Move::LEFT:
                pixX -= speed;
             break;

             case jlug::Move::RIGHT:
                pixX += speed;
             break;

             case jlug::Move::NONE:
             default:
                if (pixX%tileWidth != 0)
                {
                    altSpeed = speed;
                    std::cout << "X(" << pixX << ":" << x << ")" << std::endl;

                    // Pix between the current tile and the next tile

                    if (previousDirection == jlug::Move::RIGHT)
                        pixbetween = ABS(((x+1)*16)-static_cast<int>(pixX));
                    else if (previousDirection == jlug::Move::LEFT)
                        pixbetween = ABS(((x-1)*16)-static_cast<int>(pixX));


                    while (pixbetween < altSpeed) // If speed is too big, we reduce it.
                        altSpeed /= 2;

                    // Then, we go to this next tile

                    if (previousDirection == jlug::Move::RIGHT)
                        pixX += altSpeed;
                    else if (previousDirection == jlug::Move::LEFT)
                        pixX -= altSpeed;
                }
                else if (pixY%tileHeight != 0)
                {
                    altSpeed = speed;

                    // Pix between the current tile and the next tile

                    if (previousDirection == jlug::Move::DOWN)
                        pixbetween = ABS(((y+1)*16)-static_cast<int>(pixY));
                    else if (previousDirection == jlug::Move::UP)
                        pixbetween = ABS(((y-1)*16)-static_cast<int>(pixY));


                    while (pixbetween < altSpeed) // If speed is too big, we reduce it.
                        altSpeed /= 2;

                    // Then, we go to this next tile

                    if (previousDirection == jlug::Move::DOWN)
                        pixY += altSpeed;
                    else if (previousDirection == jlug::Move::UP)
                        pixY -= altSpeed;
                }
                else
                    isMoving = false;
             break;
         }
     }

     // Refreshing tile position with pixel position

     if (ABS((x*static_cast<int>(tileWidth))-static_cast<int>(pixX)) >= static_cast<int>(tileWidth))
        x = static_cast<int>(pixX)/static_cast<int>(tileWidth);
     if (ABS((y*static_cast<int>(tileHeight))-static_cast<int>(pixY)) >= static_cast<int>(tileHeight))
        y = static_cast<int>(pixY)/static_cast<int>(tileHeight);

     if (x < 0 || pixX < 0)
     {
        x = 0;
        pixX = 0;
     }
     else if (x >= map.getWidth()-1 || pixX >= (map.getWidth()-1)*tileWidth)
     {
        x = map.getWidth()-1;
        pixX = (map.getWidth()-1)*tileWidth;
     }

     if (y < 0 || pixX < 0)
     {
        y = 0;
        pixY = 0;
     }
     else if (y >= map.getHeight()-1 || pixY >= (map.getHeight()-1)*tileHeight)
     {
        y = map.getHeight()-1;
        pixY = y*tileHeight;
     }
 }


/**
* \brief display the character on the screen
* \param map : reference to the current map
* \param win : reference to the current window
*/

void jlug::Character::display(jlug::Map& map, jlug::Window& win)
 {
    jlug::Image sprite(IM["4.png"]);
    jlug::Rect rect;

    animate();

    rect = getCharsetRect(position, animation, sprite.getWidth(), sprite.getHeight());
    sprite.setBlitRect(rect);

    win.blit(sprite,
            pixX-map.xscroll+map.getTileWidth()/2-sprite.getWidth()/2/2, // Location - Scroll on X + centering ( tilewidth/2 - spritewidth/2 )
            pixY-map.yscroll-sprite.getHeight()/6+map.getTileHeight() // Location - Scroll on Y + putting character's feet on the tile ( tileheight - spriteheight )
            );
 }


/**
* \brief animate the character
*/

void jlug::Character::animate(void)
 {
     clock_t now(clock());
     if (isMoving)
     {
         //std::cout << "now-lastAnimation/CLOCK(" << static_cast<double>(static_cast<double>(now-lastAnimation)/CLOCKS_PER_SEC) << ") > " << animationTime << std::endl;
         if (static_cast<double>(static_cast<double>(now-lastAnimation)/CLOCKS_PER_SEC) > animationTime)
         {
             if (animation != 0)
             {
                 previousAnimation = animation;
                 animation = 0;
             }
             else
             {
                 if (previousAnimation == 1)
                    animation = 2;
                 else if (previousAnimation == 2)
                    animation = 1;
             }
             lastAnimation = now;
             //std::cout << "OK" << std::endl;
         }
     }
     else
        animation = 0;
 }

/**
* \brief make character moving
* \param dir : character's move direction and character's position
* \param speedParam : Facultative. New speed.
*/

void jlug::Character::setMove(const jlug::Move::Direction& dir, unsigned int speedParam)
 {
     setDirection(dir);
     setPosition(dir);
     if (speedParam > 0)
        setSpeed(speedParam);
 }

/**
* \brief get charset's rect in order to obtain the sprite of a position
* \param pos : character's position
* \param move : Facultative. State of character's moving.
* \param width : Facultative. Width of the charset.
* \param height : Facultative. Height of the charset.
*/

jlug::Rect jlug::Character::getCharsetRect(const jlug::Move::Direction& pos, unsigned int move, unsigned int width, unsigned int height)
 {
     jlug::Rect rect = {0, 0, 1, 1};

     // The following values are all constants.

     switch (pos)
     {
         default:
         case jlug::Move::DOWN:
            if (move == 0)
            {
                rect.x = 1;
                rect.y = 0;
            }
            else if (move == 1)
            {
                rect.x = 1;
                rect.y = 2;
            }
            else if (move == 2)
            {
                rect.x = 1;
                rect.y = 3;
            }
         break;

         case jlug::Move::UP:
            if (move == 0)
            {
                rect.x = 0;
                rect.y = 0;
            }
            else if (move == 1)
            {
                rect.x = 0;
                rect.y = 2;
            }
            else if (move == 2)
            {
                rect.x = 0;
                rect.y = 3;
            }
         break;

         case jlug::Move::LEFT:
            if (move == 0)
            {
                rect.x = 0;
                rect.y = 1;
            }
            else if (move == 1)
            {
                rect.x = 0;
                rect.y = 4;
            }
            else if (move == 2)
            {
                rect.x = 0;
                rect.y = 5;
            }
         break;

         case jlug::Move::RIGHT:
            if (move == 0)
            {
                rect.x = 1;
                rect.y = 1;
            }
            else if (move == 1)
            {
                rect.x = 1;
                rect.y = 4;
            }
            else if (move == 2)
            {
                rect.x = 1;
                rect.y = 5;
            }
         break;

     }

     rect.x *= width/2;
     rect.y *= height/6;
     rect.w *= width/2;
     rect.h *= height/6;

     return rect;
 }
