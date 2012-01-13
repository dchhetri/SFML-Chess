//
//  Pawn.h
//  ChessGame
//
//  Created by Dibash Chhetri on 1/9/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#ifndef ChessGame_Pawn_h
#define ChessGame_Pawn_h

#include "ChessBoard.h"
#include "ChessPiece.h"
#include <string>
#include <SFML/Graphics.hpp>

namespace ChessGame
{
    class Pawn : public IChessPiece
    {
    private:
        
    public:
        Pawn();
        
        //draws the chess piece
        void draw(sf::RenderWindow&)const ;
        
        //moves the chess piece to the new location
        void animateTo(const sf::Vector2f& offsetPosition) ;
        
        //shows possible move location of where the piece could move to
        void showPossibleMoveLocation(ChessBoard& gameBoard)const;
    };
}
#endif
