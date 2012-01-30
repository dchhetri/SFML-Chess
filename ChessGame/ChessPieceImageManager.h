//
//  ChessPieceImageManager.h
//  ChessGame
//
//  Created by Dibash Chhetri on 1/9/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#ifndef ChessGame_ChessPieceImageManager_h
#define ChessGame_ChessPieceImageManager_h

#include <SFML/Graphics/Image.hpp>
#include "details.h"
namespace ChessGame 
{
    
    //Defines a class to cache chess piece image 
    class ChessPieceImageManager{
    private:
        enum{ NUM_OF_PIECES = 6};
        enum{ NUM_OF_COLORS = 2};
        typedef sf::Image ChessPieceList[NUM_OF_PIECES][NUM_OF_COLORS];
    private:
        //holds the chess piece images
        static ChessPieceList imageList;
    public:
        //loads images, only needed to be called once
        static void initialize();
        //returns the specified piece
        static const sf::Image& getChessPieceImage(detail::IChessPieceEnums::PieceType, detail::IChessPieceEnums::PieceId);
    };

}
#endif
