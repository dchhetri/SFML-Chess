//
//  PromotionPiecePicker.h
//  ChessGame
//
//  Created by Dibash Chhetri on 1/26/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#ifndef ChessGame_PromotionPiecePicker_h
#define ChessGame_PromotionPiecePicker_h


#include "details.h"

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

namespace ChessGame
{
    //A class that represents a popup type window which
    //returns the choice of piece the user picks for pawn promotion
    class PromotionPiecePicker
    {
    private:
        sf::RenderWindow m_window;  
        const sf::RenderWindow& mainWindow;
    public:
        PromotionPiecePicker(const sf::RenderWindow& mainWindow);
        //displays window and returns user's pick
        detail::IChessPieceEnums::PieceType getUserPick();
    };
}
#endif
