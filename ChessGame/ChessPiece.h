//
//  ChessPiece.h
//  ChessGame
//
//  Created by Dibash Chhetri on 1/8/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#ifndef ChessGame_ChessPiece_h
#define ChessGame_ChessPiece_h

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include "ChessBoard.h"
#include "details.h"

namespace ChessGame 
{
    
    class ChessBoard;
    
   
    
    //represents an abstract chess piece interface
    class IChessPiece : public detail::IChessPieceEnums
    {
    public:   
        //draws the chess piece
        virtual void draw(sf::RenderWindow& canvas)const = 0;
        
        //moves the chess piece to the new location
        virtual void animateTo(const sf::Vector2f& offsetPosition) = 0;
        
        //shows possible move location of where the piece could move to
        virtual void showPossibleMoveLocation(ChessBoard& gameBoard)const = 0;
        
        //returns the possible move location in ChessBoard::BoardSlot position
        virtual std::vector<sf::Vector2i> getPossibleMoveLocation(ChessBoard& gameBoard)const = 0;
        
        //returns the types chess piece
        detail::IChessPieceEnums::PieceType pieceType()const;
        
        //returns constant sprite object
        const sf::Sprite& getSprite()const;
        
        //returns the sprite object
        sf::Sprite& getSprite();
        
        //sets new position
        void setPosition(const sf::Vector2f& newPosition);
        
        //set direction
        void setPieceDirection(const detail::IChessPieceEnums::PieceDirection& dir);
        
        //get current move direction
        PieceDirection getPieceDirection()const;
        
        //set the current piece id
        void setPieceID(const detail::IChessPieceEnums::PieceId& id);
        
        //get the current piece id
        detail::IChessPieceEnums::PieceId getPieceID()const;
        
        //set the current piece type
        void setPieceType(const PieceType pieceType);
        
        //returns the piece type
        detail::IChessPieceEnums::PieceType getPieceType()const;
        
        virtual ~IChessPiece(){}
        
    protected:
        PieceType       m_pieceType; //type of chess piece
        sf::Sprite      m_sprite; // chess sprite 
        PieceDirection  m_direction;
        PieceId         m_pieceId;
        
    protected:
        enum HighlightedStatus{ EMPTY_SLOT_HIGHLIGHTED, ENEMY_SLOT_HIGHLIGHTED, NOT_HIGHLIGHTED};
        //trys to highlight the the slot if not occupied or occupied with enemy
        HighlightedStatus _tryToHighlight(ChessBoard& board,const sf::Vector2i& index)const;
        //check if the slot can be highlighted, returns the status of the check
        HighlightedStatus _canHighlightSlot(ChessBoard& gameBoard, const sf::Vector2i& index)const;
    };
}

#endif
