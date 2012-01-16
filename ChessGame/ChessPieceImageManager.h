//
//  ChessPieceImageManager.h
//  ChessGame
//
//  Created by Dibash Chhetri on 1/9/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#ifndef ChessGame_ChessPieceImageManager_h
#define ChessGame_ChessPieceImageManager_h

#include <SFML/Graphics.hpp>
#include <boost/array.hpp>

namespace ChessGame 
{
    
    //Defines a class to cache chess piece image 
    class ChessPieceImageManager{
    private:
        enum{ PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, BACKGROUND_IMAGE, LIST_SIZE};
        typedef boost::array< sf::Image , LIST_SIZE > ChessPieceList;
    private:
        //holds the chess piece images
        static ChessPieceList imageList;
    public:
        //loads images, only needed to be called once
        static void initialize();
        
        //returns the pawn image
        static const sf::Image& getPawnImage();
        
        //returns the knight image
        static const sf::Image& getKnightImage();
        
        //returns the bishop image
        static const sf::Image& getBishopImage();
        
        //returns the rook image
        static const sf::Image& getRookImage();
        
        //returns the queen image
        static const sf::Image& getQueenImage();
        
        //returns the king image
        static const sf::Image& getKingImage();
        
        //returns the background image for the game
        static const sf::Image& getChessGameBackgroundImage();
    };

}
#endif
