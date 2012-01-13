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
        enum PieceDirection{ UP = 1 , DOWN  = -1};
        enum PieceId{ WHITE_PIECE_ID, BLACK_PIECE_ID };
    public:
        
        //draws the chess piece
        virtual void draw(sf::RenderWindow& canvas)const = 0;
        
        //moves the chess piece to the new location
        virtual void animateTo(const sf::Vector2f& offsetPosition) = 0;
        
        //shows possible move location of where the piece could move to
        virtual void showPossibleMoveLocation(ChessBoard& gameBoard)const = 0;
        
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
        //set direction
        void setPieceDirection(const PieceDirection& dir){ 
            m_direction = dir; 
        }
        //get current move direction
        PieceDirection getPieceDirection()const{ 
            return m_direction;
        }
        //set the current piece id
        void setPieceID(const PieceId& id){
            m_pieceId = id;
        }
        //get the current piece id
        PieceId getPieceID()const{
            return m_pieceId;
        }
        virtual ~IChessPiece(){}
        
    protected:
        PieceType       m_pieceType; //type of chess piece
        sf::Sprite      m_sprite; // chess sprite 
        PieceDirection  m_direction;
        PieceId         m_pieceId;
    };
}

#endif
