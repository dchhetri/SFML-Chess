//
//  Pawn.cpp
//  ChessGame
//
//  Created by Dibash Chhetri on 1/9/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#include "Pawn.h"
#include "ChessPieceImageManager.h"
#include <iostream>
using namespace std;
namespace ChessGame {
    
    Pawn::Pawn(){
        m_pieceType = PAWN;
        m_sprite.SetImage(ChessPieceImageManager::getPawnImage());
    }
    
    //draws the chess piece
    void Pawn::draw(sf::RenderWindow& canvas)const {
        canvas.Draw(m_sprite);
    }
    
    //moves the chess piece to the new location
    void Pawn::animateTo(const sf::Vector2f& offsetPosition) {
        m_sprite.Move(offsetPosition);
    }
    //returns the possible move location in ChessBoard::BoardSlot position
    std::vector<sf::Vector2i> Pawn::getPossibleMoveLocation(ChessBoard& gameBoard)const{
        std::vector<sf::Vector2i> possiblePositions;
        sf::Vector2i spritePos( int(m_sprite.GetPosition().x),int(m_sprite.GetPosition().y));
        sf::Vector2i slotPos = gameBoard.convertToBoardIndex(spritePos.x,spritePos.y);
        const int rowToMoveTo = slotPos.x + m_direction;
        //check if can move forward first
        if( (m_direction == UP && rowToMoveTo < ChessBoard::BOARD_HEIGHT )|| (m_direction == DOWN && rowToMoveTo >= 0))
        {
            //pawn can move one step forward
            if(!gameBoard.isOccupied(rowToMoveTo, slotPos.y) ){ 
                possiblePositions.push_back(sf::Vector2i(rowToMoveTo,slotPos.y));
            }
            
            //check within bounds on left-diagnoal
            if(slotPos.y + 1 < ChessBoard::BOARD_WIDTH){
                //if occupied highlight it to show that we can eat it
                if( gameBoard.isOccupiedWithEnemy(rowToMoveTo, slotPos.y + 1,m_pieceId))
                {
                    //gameBoard.makeHighlighted(rowToMoveTo, slotPos.y + 1);
                    possiblePositions.push_back(sf::Vector2i(rowToMoveTo,slotPos.y + 1));
                }
            }
            //check within bounds on right diagnol
            if(slotPos.y - 1 >= 0){ 
                if( gameBoard.isOccupiedWithEnemy(rowToMoveTo, slotPos.y - 1,m_pieceId))
                {
                    possiblePositions.push_back(sf::Vector2i(rowToMoveTo,slotPos.y - 1));                    
                }
            }
        }
        return possiblePositions;
    }

    //shows possible move location of where the piece could move to
    void Pawn::showPossibleMoveLocation(ChessBoard& gameBoard)const{
        std::vector<sf::Vector2i> possibleLocation = getPossibleMoveLocation(gameBoard);
        for(int i = 0; i < possibleLocation.size(); ++i){
            const sf::Vector2i& vec = possibleLocation[i];
            gameBoard.makeHighlighted(vec.x, vec.y);
        }
    }

}