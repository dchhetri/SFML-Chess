//
//  ChessBoard.h
//  ChessGame
//
//  Created by Dibash Chhetri on 1/9/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#ifndef ChessGame_ChessBoard_h
#define ChessGame_ChessBoard_h

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include "ChessPiece.h"
#include "details.h"
#include <vector>


namespace ChessGame 
{
    
    class IChessPiece;
    
    //Defines a class for chessboard
    //Handles most chess logic
    class ChessBoard
    {
     public:
        //Defines board size and each cell size
        enum{ BOARD_WIDTH = 8, BOARD_HEIGHT = 8, CELL_SIZE = 50 };
        //A status for a square in chess board
        enum BoardStatus{EMPTY, OCCUPIED, HIGHLIGHTED};
        //Defines a chessboard square
        struct BoardSlot
        {
            sf::Sprite rect;
            boost::shared_ptr<IChessPiece> piece;
            BoardStatus status;
        };
        static const sf::Vector2i BAD_INDEX;
     private:
        typedef boost::shared_ptr<IChessPiece> PiecePtr;
        typedef boost::array< PiecePtr, 16 > PieceSet;
        typedef boost::array< boost::array<BoardSlot, BOARD_WIDTH>, BOARD_HEIGHT > BoardType;
        typedef std::vector< sf::Vector2i > HighlightedList;
        enum{SPRITE_SIZE = int(CELL_SIZE*0.75)};
     private:
        BoardType m_board;
        sf::Sprite m_background;
        sf::Vector2f m_position;
        PieceSet m_whitePieceSet;
        PieceSet m_blackPieceSet;
        HighlightedList m_highlightedList; //holds slot that has been highlighted
     public:
        ChessBoard();
        ChessBoard(PieceSet& whitePieces, PieceSet& blackPieces);
        
        //draws the board given canvas
        void draw(sf::RenderWindow& canvas)const;

        //move the piece in oldSlot to the newSlot
        //if the new slot contains piece, it will get devoured and eaten
        void moveChessPiece(BoardSlot& oldSlot, BoardSlot& newSlot);
        
        //returns the constant slot in position (x,y)
        const BoardSlot& getSlot(int row, int col)const;
        
        //returns the slot in position (x,y)
        BoardSlot& getSlot(int row, int col);
        
        //returns true if current slot is occupied
        bool isOccupied(int row, int col)const;
        
        //returns true if the slot is occupied with enemy
        bool isOccupiedWithEnemy(int row, int col,const detail::IChessPieceEnums::PieceId& pieceId);
        
        //repositions the pieces to its initial position
        void reset();
        
        //positions the two set of pieces to its initial start position
        void populate(PieceSet& set1, PieceSet& set2);

        //makes position highlighted
        void makeHighlighted(int x, int y);
        
        //clears highlighted entries if any
        void clearHighlightedEntries();
        
        //returns the top left corner of the board
        sf::Vector2f getPosition()const;

        //returns true if the point is inside the board
        bool contains(int winX, int winY)const;

        //returns the slot from window coordinates
        //if invalid coordinates provided, returns ChessBoard::BAD_INDEX
        sf::Vector2i convertToBoardIndex(int winX, int winY)const;
        
    private:
        /*** helper functions ***/
        void _initialize();
        //calculates the offset of the sprite position to be placed at cell_i
        float _calculateSpriteOffset()const;
    };

}
#endif
