#ifndef CHARACTER_HPP_INCLUDED
#define CHARACTER_HPP_INCLUDED

/**
* \file character.hpp
* \author JirialMovie
*/

#include "imagemanager.hpp"
#include "window.hpp"
#include "map.hpp"
#include "utils.hpp"


/**
* \namespace jlug
* \brief All jLug components.
* All jLug components.
*/
namespace jlug
{
    /**
    * \class Character
    * \brief Interactive and movable objects on the map
    */

    class Character
    {

        public:
            Character(void);
            Character(unsigned int cid, const std::string& cname);
            Character(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy);
            Character(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, unsigned int posz);
            ~Character(void);

            void setX(unsigned int posx);
            void setY(unsigned int posy);
            void setZ(unsigned int posz);
            void setCoord(unsigned int posx, unsigned int posy);
            void setCoord(unsigned int posx, unsigned int posy, unsigned int posz);
            void setCharset(unsigned int cid);
            void setName(const std::string& cname);
            void setPosition(const jlug::Move::Direction& pos);
            void setDirection(const jlug::Move::Direction& dir);
            void setSpeed(unsigned int speedParam);

            void setMove(const jlug::Move::Direction& dir, unsigned int speedParam = 0);

            unsigned int getX(void);
            unsigned int getY(void);
            unsigned int getZ(void);
            jlug::Rect getCoord(void);
            unsigned int getCharset(void);
            const std::string& getName(void);
            const jlug::Move::Direction& getPosition(void);
            const jlug::Move::Direction& getDirection(void);
            unsigned int getSpeed(void);


            virtual void checkCollisions(jlug::Map& map);
            virtual void move(jlug::Map& map);
            virtual void display(jlug::Map& map, jlug::Window& win);
            virtual void displayUsername(jlug::Window& win);


            virtual void animate(void);

            bool checkTile(jlug::Map& map, int tileX, int tileY);
            static jlug::Rect getCharsetRect(const jlug::Move::Direction& pos, unsigned int move = 0, unsigned int width = 2, unsigned int height = 6);



        protected:
            unsigned int charset; /*!< ID of the character's charset */
            std::string name; /*!< Name of the character. May be empty, displayed otherwise. */
            std::string charsetFilename; /*!< Path to the charset's file */


            signed int x; /*!< X-position */
            signed int y; /*!< Y-position */
            signed int z; /*!< Z-position */

            signed int pixX; /*!< X-position in pixels */
            signed int pixY; /*!< Y-position in pixels */

            jlug::Move::Direction position; /*!< sprite's position */
            jlug::Move::Direction direction; /*!< move direction */
            jlug::Move::Direction previousDirection; /*!< previous move direction */
            int speed; /*!< Velocity in pixels */

            bool isMoving;
            unsigned char animation;
            unsigned char previousAnimation;
            clock_t lastAnimation;
            double animationTime;

            jlug::Point worldCoordinates; /*! < Coordinates in a 3D world */
    };

    typedef Character NPC;
}

#endif // CHARACTER_HPP_INCLUDED
