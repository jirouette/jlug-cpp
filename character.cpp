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

jlug::Character::Character(void):
                        charset(0), name(""), charsetFilename(""), x(0), y(0), z(0), pixX(x*16), pixY(y*16),
                        position(jlug::Move::DOWN), direction(jlug::Move::NONE), previousDirection(jlug::Move::NONE), speed(4), 
                        isMoving(false), animation(0), previousAnimation(1), lastAnimation(clock()), animationTime(0.2)
{
    std::ostringstream buffer;
    buffer << charset;
    charsetFilename += buffer.str();
    charsetFilename += ".png";
}

/**
* \brief Constructor
* \param cid : Charset ID
* \param name : Character's name. May be empty.
* \param imageM : reference to the ImageManager instance.
*
* Initialisize everything.
*/

jlug::Character::Character(unsigned int cid, const std::string& cname):
                        charset(cid), name(cname), charsetFilename(""), x(0), y(0), z(0), pixX(x*16), pixY(y*16),
                        position(jlug::Move::DOWN), direction(jlug::Move::NONE), previousDirection(jlug::Move::NONE), speed(4), 
                        isMoving(false), animation(0), previousAnimation(1), lastAnimation(clock()), animationTime(0.2)
{
    std::ostringstream buffer;
    buffer << charset;
    charsetFilename += buffer.str();
    charsetFilename += ".png";
}

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

jlug::Character::Character(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy):
                        charset(cid), name(cname), charsetFilename(""), x(posx), y(posy), z(0), pixX(x*16), pixY(y*16),
                        position(jlug::Move::DOWN), direction(jlug::Move::NONE), previousDirection(jlug::Move::NONE), speed(4),
                        isMoving(false), animation(0), previousAnimation(1), lastAnimation(clock()), animationTime(0.2)
{
    std::ostringstream buffer;
    buffer << charset;
    charsetFilename += buffer.str();
    charsetFilename += ".png";
}

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

jlug::Character::Character(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, unsigned int posz):
                        charset(cid), name(cname), charsetFilename(""), x(posx), y(posy), z(posz), pixX(x*16), pixY(y*16), 
                        position(jlug::Move::DOWN), direction(jlug::Move::NONE), previousDirection(jlug::Move::NONE), 
                        speed(4), isMoving(false), animation(0), previousAnimation(1), lastAnimation(clock()), animationTime(0.2)
{
    std::ostringstream buffer;
    buffer << charset;
    charsetFilename += buffer.str();
    charsetFilename += ".png";
}



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
     jlug::Rect coord(x, y, 0, 0);
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
* \brief check collisions
* \param map : reference to the current map
*/

void jlug::Character::checkCollisions(jlug::Map& map)
 {
     int tileWidth(map.getTileWidth()), tileHeight(map.getTileHeight());
     int tileX(x), tileY(y);
     int newspeed(speed);

     if (direction != jlug::Move::NONE && speed > 0)
         switch (direction)
         {
             case jlug::Move::LEFT:
                tileX = (pixX-speed<0)?-1:(pixX-speed)/tileWidth; // checking the previous tile
                for (int i(x) ; i >= tileX ; --i)
                    if (!checkTile(map, i, y))
                    {
                         // affecting speed with pixels left between the current position and the last allowed position
                        newspeed = pixX-(i+1)*tileWidth;
                        i = tileX-1;
                    }
                break;

             case jlug::Move::RIGHT:
                tileX = (pixX+((speed<tileWidth*2)?tileWidth*2:speed))/tileWidth; // checking the most probable tile
                for (int i(x) ; i <= tileX ; ++i)
                    if (!checkTile(map, i, y))
                    {
                         // affecting speed with pixels left between the current position and the last allowed position
                        newspeed = (i-1)*tileWidth-pixX;
                        i = tileX+1;
                    }
                break;

             case jlug::Move::UP:
                tileY = (pixY-speed<0)?-1:(pixY-speed)/tileHeight; // checking the previous tile
                for (int j(y) ; j >= tileY ; --j)
                    if (!checkTile(map, x, j))
                    {
                         // affecting speed with pixels left between the current position and the last allowed position
                        newspeed = pixY-(j+1)*tileHeight;
                        j = tileY-1;
                    }
                break;

             case jlug::Move::DOWN:
                tileY = (pixY+((speed<tileHeight*2)?tileHeight*2:speed))/tileHeight; // check the most probable tile
                for (int j(y) ; j <= tileY ; ++j)
                    if (!checkTile(map, x, j))
                    {
                         // affecting speed with pixels left between the current position and the last allowed position
                        newspeed = (j-1)*tileHeight-pixY;
                        j = tileY+1;
                    }
                break;


            default:
                // Nothing to do.
                break;
         }
     if (newspeed < 0)
        newspeed = 0;
     if (newspeed < speed)
        speed = newspeed;
 }


/**
* \brief check if the character can go on a tile
* \param map : reference to the current map
* \param tileX : X-position of the tile
* \param tileY : Y-position of the tile
* \return boolean
*/

bool jlug::Character::checkTile(jlug::Map& map, int tileX, int tileY)
 {
    int width(map.getWidth()), height(map.getHeight());
    if (tileX < 0 || tileY < 0 || tileX >= width || tileY >= height)
        return false;
    return true;
 }

/**
* \brief move the character
* \param map : reference to the current map
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


                    while (static_cast<unsigned int>(pixbetween) < altSpeed) // If speed is too big, we reduce it.
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


                    while (static_cast<unsigned int>(pixbetween) < altSpeed) // If speed is too big, we reduce it.
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

     if (ABS((x*static_cast<int>(tileWidth))-static_cast<int>(pixX)) >= static_cast<int>(tileWidth) || static_cast<int>(pixX)%static_cast<int>(tileWidth) == 0)
        x = static_cast<int>(pixX)/static_cast<int>(tileWidth);
     if (ABS((y*static_cast<int>(tileHeight))-static_cast<int>(pixY)) >= static_cast<int>(tileHeight)  || static_cast<int>(pixY)%static_cast<int>(tileHeight) == 0)
        y = static_cast<int>(pixY)/static_cast<int>(tileHeight);

 }

/**
* \brief calculate depth of the character with his position on the map
* \param map : reference to the Map
* \return depth
*/
double jlug::Character::getDepthByTile(jlug::Map& map)
{
    const jlug::TileProp& tile(map.getTile(static_cast<int>(pixX/map.getTileWidth()),
                                     static_cast<int>(pixY/map.getTileHeight()),
                                     static_cast<int>(z)));
    const int posX(pixX%map.getTileWidth()), posY(pixY%map.getTileHeight());
    const int middleX(map.getTileWidth()/2), middleY(map.getTileHeight()/2);

    // PosY is center
    if (posX == middleX && posY == middleY)
        return ((tile.upperLeftCorner.z + tile.upperRightCorner.z)+
               (tile.downerLeftCorner.z +tile.downerRightCorner.z))
               /4.0;
    else if (posX < middleX && posY == middleY)
        return ((tile.upperLeftCorner.z + tile.downerLeftCorner.z)+
               (tile.upperRightCorner.z + tile.downerRightCorner.z)/2.0)
               /3.0;
    else if (posX > middleX && posY == middleY)
        return ((tile.upperRightCorner.z + tile.downerRightCorner.z)+
               (tile.upperLeftCorner.z + tile.downerLeftCorner.z)/2.0)
               /3.0;
    
    // PosY is upper part
    else if (posX == middleX && posY > middleY)
        return ((tile.upperLeftCorner.z + tile.upperRightCorner.z)+
               (tile.downerLeftCorner.z +tile.downerRightCorner.z)/2.0)
               /3.0;
    else if (posX < middleX && posY > middleY)
        return ((tile.upperLeftCorner.z + tile.upperRightCorner.z)+
               (tile.downerLeftCorner.z))
               /3.0;
    else if (posX > middleX && posY > middleY)
        return ((tile.upperLeftCorner.z + tile.upperRightCorner.z)+
               (tile.downerRightCorner.z))
               /3.0;

    // PosY is downer part
    else if (posX == middleX && posY < middleY)
        return ((tile.downerLeftCorner.z + tile.downerRightCorner.z)+
               (tile.upperLeftCorner.z +tile.upperRightCorner.z)/2.0)
               /3.0;
    else if (posX < middleX && posY < middleY)
        return ((tile.downerLeftCorner.z + tile.downerRightCorner.z)+
               (tile.upperLeftCorner.z))
               /3.0;
    else if (posX > middleX && posY < middleY)
        return ((tile.downerLeftCorner.z + tile.downerRightCorner.z)+
               (tile.upperRightCorner.z))
               /3.0;
    return 0.0;
}


/**
* \brief display the character on the screen
* \param map : reference to the current map
* \param win : reference to the current window
*/

void jlug::Character::display(jlug::Map& map, jlug::Window& win)
 {
    std::ostringstream buffer;
    jlug::Image& sprite(jlug::ImageManager::getInstance()[charsetFilename]);
    jlug::Rect rect;
    jlug::Square square;

    // Roll the animation before displaying an only frame
    animate();

    rect = getCharsetRect(position, animation, sprite.getWidth(), sprite.getHeight());
    sprite.setBlitRect(rect);

    worldCoordinates.x = static_cast<int>(pixX/map.getTileWidth()-(sprite.getWidth()/2/2)*1.0/map.getTileWidth());
    worldCoordinates.y = static_cast<int>(pixY/map.getTileHeight()-sprite.getHeight()/6*1.0/map.getTileHeight()+1);
    worldCoordinates.z = getDepthByTile(map);

    square.setPixelTranslation(map.getTileWidth(), map.getTileHeight());

    // Initial position
    square.setPosition(worldCoordinates);

    // Transformations

    square.rotate(30, 0, 0);
    square.scale(rect.w, rect.h, 1);

    //Texturing

    square.setTextureSize(0, 0, sprite.getRealWidth(), sprite.getRealHeight());
    square.setTextureZone(rect.x, rect.y, rect.w, rect.h);
    square.setTexture(jlug::ImageManager::getInstance().getTexture(charsetFilename));

    // Finally ! 
    square.draw();

    buffer << "(" << x << ", " << y << ") Speed = " << speed << "\n\n(" << pixX << ", " << pixY << ")";
    buffer << std::endl;
    buffer << "worldCoordinates(" << worldCoordinates.x << ", " << worldCoordinates.y;
    buffer << ", " << worldCoordinates.z << ")" << std::endl;
    win.debug(buffer.str());
 }

void jlug::Character::displayUsername(jlug::Window& win)
{
    win.getWidth();
    /*GLdouble projectionMatrix[16], modelviewMatrix[16], screenCoordinates[3];

    glGetDoublev(GL_PROJECTION_MATRIX, projectionMatrix);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelviewMatrix);

    gluProject(worldCoordinates.x, worldCoordinates.y, worldCoordinates.z,
    modelviewMatrix, projectionMatrix, 0,
    (screenCoordinates), &(screenCoordinates[1]), &(screenCoordinates[2]));

    win.text("Patate", screenCoordinates[0], screenCoordinates[1]);*/
    // Yeah, this method does absolutely nothing. 

}


/**
* \brief animate the character
*/

void jlug::Character::animate(void)
 {
     clock_t now(clock());
     if (isMoving)
     {
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
     jlug::Rect rect(0, 0, 1, 1);

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
