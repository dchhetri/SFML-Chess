//
//  PromotionPiecePicker.h
//  ChessGame
//
//  Created by Dibash Chhetri on 1/26/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#ifndef ChessGame_PromotionPiecePicker_h
#define ChessGame_PromotionPiecePicker_h


#include "ChessPiece.h"
#include "details.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <boost/shared_ptr.hpp>

namespace ChessGame
{
    //A class that represents a popup type window which
    //returns the choice of piece the user picks for pawn promotion
    class PromotionPiecePicker
    {
    private:
        enum {ROW_SIZE = 2, COL_SIZE = 2};
        typedef boost::shared_ptr<IChessPiece> PieceType;
        sf::RenderWindow m_window;  
        const sf::RenderWindow& mainWindow;
        PieceType m_pieceOptions[ROW_SIZE][COL_SIZE];
        detail::IChessPieceEnums::PieceId m_color;
    public:
        PromotionPiecePicker(const sf::RenderWindow& mainWindow, detail::IChessPieceEnums::PieceId color);
        //displays window and returns user's pick
        detail::IChessPieceEnums::PieceType getUserPick();
    private:
        //helper functions

        //displays the
        void _displaySelections();
        //checks to see if any piece option was clicked. If so,it sets type to that chess piece
        bool _onMouseClick(float x, float y, detail::IChessPieceEnums::PieceType& type);
    };
}
#endif
