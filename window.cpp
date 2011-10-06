#include "window.hpp"

/**
* \brief Constructor
* \param width : width of the window in pixels
* \param height : width of the window in pixels
* \param name : title of the window
*
* set blitRect to his max value
*/
jlug::Window::Window(unsigned int width, unsigned int height, const std::string& name):
                        win(sf::VideoMode(width, height, 32), name, sf::Style::Close|sf::Style::Titlebar),
                        debugStr(""), font(), winstr()
 {
     blitRect.x = blitRect.y = 0;
     blitRect.w = width;
     blitRect.h = height;

     font.LoadFromFile("Arial.ttf");
     winstr.SetFont(font);
     winstr.SetSize(12);


    glEnable(GL_TEXTURE_2D); 
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.f, static_cast<double>(width)/static_cast<double>(height), 1.f, 500.f);

 }

/**
* \brief Destructor
*
* Close the window if still opened.
*/
jlug::Window::~Window(void)
 {
     if (win.IsOpened())
        win.Close();
 }

/**
* \brief Close the window
*/
void jlug::Window::close(void)
 {
     win.Close();
 }

/**
* \brief Listen the events
* Refresh the input.
*/
void jlug::Window::processEvents(void)
 {
     sf::Event event;
     while (win.GetEvent(event))
        if (event.Type == sf::Event::Closed)
            win.Close();
        else if (event.Type == sf::Event::Resized)
            glViewport(0, 0, event.Size.Width, event.Size.Height);
 }

/**
* \brief Set the Blit Rect
* \param rect : new rect which will delimits the blit process.
*
* The methods checks if each datafield is correct and then affects them to the current blitRect or lets the current values.
*/
void jlug::Window::setBlitRect(const jlug::Rect& rect)
 {
     blitRect.x = (rect.x >= 0 && rect.x < win.GetWidth()) ? rect.x : blitRect.x; // negative or superior to width rect.x is not allowed.
     blitRect.y = (rect.y >= 0 && rect.y < win.GetHeight()) ? rect.y : blitRect.y; // negative or superior to height rect.y is not allowed.
     blitRect.w = (rect.w > 0 && rect.w <= win.GetWidth()-blitRect.x) ? rect.w : blitRect.w; // negative or null or inferior to the left width rect.w is not allowed.
     blitRect.h = (rect.h > 0 && rect.h <= win.GetHeight()-blitRect.y) ? rect.h : blitRect.h; // negative or null or inferior to the left height rect.h is not allowed.
 }

/**
* \brief Set the Blit Rect
* \param x : X position
* \param y : Y position
* \param w : width of the blit rect
* \param h : height of the blit rect
*
* Creates a jlug::Rect and calls setBlitRect(const jlug::Rect& rect);
*/
void jlug::Window::setBlitRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h)
 {
     jlug::Rect rect = {x, y, w, h};
     setBlitRect(rect);
 }

/**
* \brief display image to the screen
* \param img : the image which will be displayed
*
* the window's blitrect and the image's blitrect will delimit the displaying of the image.
*/
void jlug::Window::blit(jlug::Image& img)
 {
    if (img.blitRect.w > blitRect.w)
        img.blitRect.w = blitRect.w;
    if (img.blitRect.h > blitRect.h)
        img.blitRect.h = blitRect.h;

    img.image.SetSubRect(sf::IntRect(img.blitRect.x, img.blitRect.y, img.blitRect.x+img.blitRect.w, img.blitRect.y+img.blitRect.h));
    img.image.SetPosition(blitRect.x, blitRect.y);
    //win.Draw(img.image);
    //win.Draw(img.image);
 }

/**
* \brief display image to the screen
* \param img : the image which will be displayed
* \param x : quick value to position the image on X-axe
* \param y : quick value to position the image on Y-axe
*
* the window's blitrect and the image's blitrect will delimit the displaying of the image.
*/
void jlug::Window::blit(jlug::Image& img, int x, int y)
 {
     blitRect.x = x;
     blitRect.y = y;
     blitRect.w = win.GetWidth() - x;
     blitRect.h = win.GetHeight() - y;

     blit(img);
 }

/**
* \brief display image to the screen
* \param img : the image which will be displayed
* \param pos : quick position of the image on the screen
*
* the window's blitrect and the image's blitrect will delimit the displaying of the image.
*/
void jlug::Window::blit(jlug::Image& img, const jlug::Rect& pos)
 {
     blit(img, pos.x, pos.y);
 }

/**
* \brief refresh the screen
*/
void jlug::Window::flip(void)
 {
     //win.Draw(winstr);
        glFlush();
     win.Display();
 }

/**
* \brief clear the screen
*/
void jlug::Window::clear(void)
 {
     win.Clear();
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     gluLookAt(0, -0.5, 1, 0, 0, 0, 0, 1, 0);
 }

/**
* \brief get width of the window
*/
unsigned int jlug::Window::getWidth(void)
 {
     return win.GetWidth();
 }

/**
* \brief get height of the window
*/
unsigned int jlug::Window::getHeight(void)
 {
     return win.GetHeight();
 }

/**
* \brief get width and height of the window
*/
jlug::Rect jlug::Window::getSize(void)
 {
     jlug::Rect rect = {0, 0, getWidth(), getHeight()};
     return rect;
 }

/**
* \brief get the user inputs from the window events
*/
const jlug::Input& jlug::Window::getInput(void)
 {
     sf::Event event;
     while (win.GetEvent(event));
     const jlug::Input& input(win.GetInput());
     return input;
 }

/**
* \brief check if the window is still open by processing the events
* \return true if the window is open, false otherwise.
*/
bool jlug::Window::isOpen(void)
 {
     processEvents();
     return win.IsOpened();
 }

/**
* \brief write a debug-text on the window.
* \param str : debugging text
*/

void jlug::Window::debug(const std::string& str)
 {
     debugStr = str;
     winstr.SetText(debugStr);
 }
