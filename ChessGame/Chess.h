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
#include "SidePanel.h"
#include "StatusBar.h"
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
     public:
        typedef boost::shared_ptr<IChessPiece> PiecePtr;
        typedef boost::array< PiecePtr, 16> PieceSet;
     private:
        bool m_isUserOneTurn;
        ChessBoard m_board;
        std::pair<User,PieceSet> m_whiteUser;
        std::pair<User,PieceSet> m_blackUser;
        ChessBoard::BoardSlot* m_lastActiveSlot;
        SidePanel<PiecePtr, 2, 8> m_leftWhiteUserPanel;
        SidePanel<PiecePtr, 2, 8> m_righBlackUsertPanel;
        StatusBar   m_statusBar;
        sf::RenderWindow& app;
        bool m_isGameOver;
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
        //returns true if its user one turn
        bool isUserOneTurn()const;
        //returns user1 id
        int getUserOneId()const;
        //returns user2 id
        int getUserTwoId()const;
        //returns true if game is over
        bool isGameOver()const;
    private:
        //private helper function
        void _initialize();
        void _onHighlightedEntryClicked(ChessBoard::BoardSlot& slot);
        void _onOccupiedEntryClicked(ChessBoard::BoardSlot& slot);
        void _alternateUserTurn();
        //adds the piece in the slot to its appropriate side panel, which represents eaten pieces
        void _addEatenPieceToSidePanel(ChessBoard::BoardSlot& slot);
        bool _isCheckmate(ChessBoard::BoardSlot& lastSlotUsed);
        bool _isStaleMate();
        
        void _onCheckmate();
        void _onGameOver();
        void _onStaleMate();
    };
}

#endif
