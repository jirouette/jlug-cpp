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
            Character(jlug::ImageManager& imageM);
            Character(unsigned int cid, const std::string& cname, jlug::ImageManager& imageM);
            Character(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, jlug::ImageManager& imageM);
            Character(unsigned int cid, const std::string& cname, unsigned int posx, unsigned int posy, unsigned int posz, jlug::ImageManager& imageM);
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


            void move(jlug::Map& map);
            void display(jlug::Map& map, jlug::Window& win);


            virtual void animate(void);
            virtual bool checkCollisions(jlug::Map& map);

            static int checkTileRow(jlug::Map& map, unsigned int tileZ, int startTileX, int startTileY, int endTileX, int endTileY);
            static jlug::Rect getCharsetRect(const jlug::Move::Direction& pos, unsigned int move = 0, unsigned int width = 2, unsigned int height = 6);



        private:
            unsigned int charset; /*!< ID of the character's charset */
            std::string name; /*!< Name of the character. May be empty, displayed otherwise. */


            signed int x; /*!< X-position */
            signed int y; /*!< Y-position */
            signed int z; /*!< Z-position */

            unsigned int pixX; /*!< X-position in pixels */
            unsigned int pixY; /*!< Y-position in pixels */

            jlug::Move::Direction position; /*!< sprite's position */
            jlug::Move::Direction direction; /*!< move direction */
            jlug::Move::Direction previousDirection; /*!< previous move direction */
            unsigned int speed; /*!< Velocity in pixels */

            bool isMoving;
            unsigned char animation;
            unsigned char previousAnimation;
            clock_t lastAnimation;
            double animationTime;


            jlug::ImageManager& IM; /*!< image manager */
    };



}

#endif // CHARACTER_HPP_INCLUDED
