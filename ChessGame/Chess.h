//
//  Chess.h
//  ChessGame
//
//  Created by Dibash Chhetri on 1/10/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#ifndef ChessGame_Chess_h
#define ChessGame_Chess_h

#include "ChessBoard.h"
#include "User.h"
#include "ChessPiece.h"
#include <utility>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <SFML/Window.hpp>

namespace ChessGame 
{
    class IChessPiece;
    
    class Chess
    {
     private:
        typedef boost::shared_ptr<IChessPiece> PiecePtr;
        typedef boost::array< PiecePtr, 16> PieceSet;
     private:
        bool m_isUserOneTurn;
        ChessBoard m_board;
        std::pair<User,PieceSet> m_whiteUser;
        std::pair<User,PieceSet> m_blackUser;
        ChessBoard::BoardSlot* m_lastActiveSlot;
        sf::RenderWindow& app;
     public:
        Chess(sf::RenderWindow& app);
        //start the game
        void play();
        //reset board
        void reset();
        //save state
        void saveState();
        //load state
        void loadState();
        //handle mouse clicked
        void onMouseClicked(int x, int y);
    private:
        //private helper function
        void _initialize();
        void _onHighlightedEntryClicked(ChessBoard::BoardSlot& slot);
        void _onOccupiedEntryClicked(ChessBoard::BoardSlot& slot);
    };
}

#endif
