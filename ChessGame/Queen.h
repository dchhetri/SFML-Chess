//
//  Queen.h
//  ChessGame
//
//  Created by Dibash Chhetri on 1/15/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#ifndef ChessGame_Queen_h
#define ChessGame_Queen_h

#include "ChessPiece.h"


namespace ChessGame 
{
    class Queen : public IChessPiece
    {
    public:
        explicit Queen(detail::IChessPieceEnums::PieceId color = detail::IChessPieceEnums::WHITE_PIECE_ID);
        
        //draws the chess piece
        void draw(sf::RenderWindow&)const ;
        
        //moves the chess piece to the new location
        void animateTo(const sf::Vector2f& offsetPosition) ;
        
        //shows possible move location of where the piece could move to
        void showPossibleMoveLocation(ChessBoard& gameBoard)const;
        
        //returns the possible move location in ChessBoard::BoardSlot position
        std::vector<sf::Vector2i> getPossibleMoveLocation(ChessBoard& gameBoard)const;

    };
}

#endif
