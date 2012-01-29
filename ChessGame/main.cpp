
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include "Chess.h"
#include "ChessPieceImageManager.h"
#include "SidePanel.h"


void setupApplication(){
    ChessGame::ChessPieceImageManager::initialize();
}

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
    using namespace std;
    
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(800, 600), "SFML OpenGL");
    
    //load in what we need
    setupApplication();
    
    // Create a clock for measuring time elapsed
    sf::Clock Clock;
  
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
        
       // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        App.Clear();
        
        chessGame.play();
        
        // Finally, display rendered frame on screen
        App.Display();    

    }
    
    return EXIT_SUCCESS;
}
