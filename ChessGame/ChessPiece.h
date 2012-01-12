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
#include <SFML/Graphics.hpp>

#include "ChessBoard.h"

namespace ChessGame 
{
    class ChessBoard;
    
    //represents an abstract chess piece interface
    class IChessPiece
    {
    public:
        enum PieceType{PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};
    public:
        
        //draws the chess piece
        virtual void draw(sf::RenderWindow& canvas)const = 0;
        
        //moves the chess piece to the new location
        virtual void animateTo(const sf::Vector2f& offsetPosition) = 0;
        
        //shows possible move location of where the piece could move to
        virtual void showPossibleMoveLocation(ChessBoard& gameBoard) = 0;
        
        //returns the types chess piece
        PieceType pieceType()const{ return m_pieceType; }
        
        //returns constant sprite object
        const sf::Sprite& getSprite()const{ return m_sprite; }
        
        //returns the sprite object
        sf::Sprite& getSprite(){ return m_sprite; }
        
        //sets new position
        void setPosition(const sf::Vector2f& newPosition){
            m_sprite.SetPosition(newPosition);
        }
        
        virtual ~IChessPiece(){}
        
    protected:
        PieceType       m_pieceType; //type of chess piece
        sf::Sprite      m_sprite; // chess sprite 
    };
}

#endif
