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



void jlug::Character::checkCollisions(jlug::Map& map)
 {
     int tileWidth(map.getTileWidth()), tileHeight(map.getTileHeight());
     int tileX(x), tileY(y);
     int newspeed(speed);

     if (direction != jlug::Move::NONE && speed > 0)
     {
         switch (direction)
         {
             case jlug::Move::LEFT:
                tileX = (pixX-speed<0)?-1:(pixX-speed)/tileWidth;
                for (int i(x) ; i >= tileX ; i--)
                    if (!checkTile(map, i, y))
                    {
                        newspeed = pixX-(i+1)*tileWidth;
                        i = tileX-1;
                    }
                break;

             case jlug::Move::RIGHT:
                tileX = (pixX+((speed<tileWidth*2)?tileWidth*2:speed))/tileWidth;
                for (int i(x) ; i <= tileX ; i++)
                    if (!checkTile(map, i, y))
                    {
                        newspeed = (i-1)*tileWidth-pixX;
                        i = tileX+1;
                    }
                break;


            default:
                break;




         }
     }
     if (newspeed < 0)
        newspeed = 0;
     if (newspeed < speed)
        speed = newspeed;
 }



bool jlug::Character::checkTile(jlug::Map& map, int tileX, int tileY)
 {
    int width(map.getWidth()), height(map.getHeight());
    if (tileX < 0 || tileY < 0 || tileX >= width || tileY >= height)
        return false;
    if (tileX == 2)
        return false;
    return true;
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

         checkCollisions(map);

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

     // Refreshing tile position with pixel position

     if (ABS((x*static_cast<int>(tileWidth))-static_cast<int>(pixX)) >= static_cast<int>(tileWidth))
        x = static_cast<int>(pixX)/static_cast<int>(tileWidth);
     if (ABS((y*static_cast<int>(tileHeight))-static_cast<int>(pixY)) >= static_cast<int>(tileHeight))
        y = static_cast<int>(pixY)/static_cast<int>(tileHeight);

 }


/**
* \brief display the character on the screen
* \param map : reference to the current map
* \param win : reference to the current window
*/

void jlug::Character::display(jlug::Map& map, jlug::Window& win)
 {
    char buffer[10];
    std::string debug("");
    jlug::Image sprite(IM["4.png"]);
    jlug::Rect rect;

    animate();

    rect = getCharsetRect(position, animation, sprite.getWidth(), sprite.getHeight());
    sprite.setBlitRect(rect);

    win.blit(sprite,
            pixX-map.xscroll+map.getTileWidth()/2-sprite.getWidth()/2/2, // Location - Scroll on X + centering ( tilewidth/2 - spritewidth/2 )
            pixY-map.yscroll-sprite.getHeight()/6+map.getTileHeight() // Location - Scroll on Y + putting character's feet on the tile ( tileheight - spriteheight )
            );

    debug += "(";
    itoa(x, buffer, 10);
    debug += buffer;
    debug += ", ";
    itoa(y, buffer, 10);
    debug += buffer;
    debug += ") Speed = ";
    itoa(speed, buffer, 10);
    debug += buffer;
    debug += "\n\n(";
    itoa(pixX, buffer, 10);
    debug += buffer;
    debug += ", ";
    itoa(pixY, buffer, 10);
    debug += buffer;
    debug += ")";

    win.debug(debug);
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
