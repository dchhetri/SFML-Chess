
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "Chess.h"
#include "ChessPieceImageManager.h"
#include "SidePanel.h"
#include <iostream>
////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
void initializeOpenGL(){
    // Set color and depth clear value
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);
    
    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    
    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 500.f);
    
    ChessGame::ChessPieceImageManager::initialize();

}

int main()
{
    using namespace std;
    
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(800, 600), "SFML OpenGL");
    
    // Create a clock for measuring time elapsed
    sf::Clock Clock;
    
    initializeOpenGL();
  
    App.SetFramerateLimit(60);
    
    ChessGame::Chess chessGame(App);
    
    // Start game loop
    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed){
                App.Close();
            }
            
            // Escape key : exit
            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)){
                App.Close();
            }
            
            // Resize event : adjust viewport
            if (Event.Type == sf::Event::Resized){
                glViewport(0, 0, Event.Size.Width, Event.Size.Height);
            }

            
            if(App.GetInput().IsMouseButtonDown(sf::Mouse::Left)){
                sf::Vector2f coord = App.ConvertCoords(App.GetInput().GetMouseX(), App.GetInput().GetMouseY());
                chessGame.onMouseClicked(coord.x, coord.y);
            }
            
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        chessGame.play();
        
        // Finally, display rendered frame on screen
        App.Display();    

    }
    
    return EXIT_SUCCESS;
}
