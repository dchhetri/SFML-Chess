//
//  Knight.cpp
//  ChessGame
//
//  Created by Dibash Chhetri on 1/14/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#include "Knight.h"
#include "ChessPieceImageManager.h"

namespace ChessGame {
    Knight::Knight(){
        m_pieceType = KNIGHT;
        m_sprite.SetImage(ChessPieceImageManager::getKnightImage());
    }
    //draws the chess piece
    void Knight::draw(sf::RenderWindow& canvas)const{
        canvas.Draw(m_sprite);
    }
    
    //moves the chess piece to the new location
    void Knight::animateTo(const sf::Vector2f& offsetPosition){
        m_sprite.Move(offsetPosition);
    }

    //returns the possible move location in ChessBoard::BoardSlot position
    std::vector<sf::Vector2i> Knight::getPossibleMoveLocation(ChessBoard& gameBoard)const{
        std::vector<sf::Vector2i> possibleLocations;
        using sf::Vector2i;
        Vector2i spritePos( int(m_sprite.GetPosition().x),int(m_sprite.GetPosition().y));
        Vector2i slotPos = gameBoard.convertToBoardIndex(spritePos.x,spritePos.y);
        Vector2i tmp;
        
        //front mid left
        tmp = Vector2i(slotPos.x + 1, slotPos.y - 2);
        if(tmp.x  < ChessBoard::BOARD_HEIGHT && tmp.y  >= 0){
            if(_canHighlightSlot(gameBoard,tmp) != NOT_HIGHLIGHTED){
                possibleLocations.push_back(tmp);
            }
        }
        //front mid right
        tmp = Vector2i(slotPos.x + 1, slotPos.y + 2);
        if(tmp.x  < ChessBoard::BOARD_HEIGHT && tmp.y < ChessBoard::BOARD_WIDTH){
            if(_canHighlightSlot(gameBoard,tmp) != NOT_HIGHLIGHTED){
                possibleLocations.push_back(tmp);
            }
        }
        //back mid left
        tmp = Vector2i(slotPos.x - 1 , slotPos.y - 2);
        if(tmp.x >= 0 &&  tmp.y >= 0){
           if(_canHighlightSlot(gameBoard,tmp) != NOT_HIGHLIGHTED){
                possibleLocations.push_back(tmp);
            }
        }
        //back mid right
        tmp = Vector2i(slotPos.x - 1, slotPos.y + 2);
        if(tmp.x >= 0 && tmp.y  < ChessBoard::BOARD_WIDTH){
           if(_canHighlightSlot(gameBoard,tmp) != NOT_HIGHLIGHTED){
                possibleLocations.push_back(tmp);
            }
        }
        //front top left
        tmp = Vector2i(slotPos.x + 2 , slotPos.y - 1);
        if(tmp.x < ChessBoard::BOARD_HEIGHT && tmp.y >= 0){
            if(_canHighlightSlot(gameBoard,tmp) != NOT_HIGHLIGHTED){
                possibleLocations.push_back(tmp);
            }            
        }
        //front top right
        tmp = Vector2i(slotPos.x + 2, slotPos.y + 1);
        if(tmp.x < ChessBoard::BOARD_WIDTH && tmp.y < ChessBoard::BOARD_WIDTH ){
            if(_canHighlightSlot(gameBoard,tmp) != NOT_HIGHLIGHTED){
                possibleLocations.push_back(tmp);
            }
        }
        //back bottom left
        tmp = Vector2i(slotPos.x - 2, slotPos.y - 1);
        if(tmp.x  >= 0 && tmp.y >= 0){
            if(_canHighlightSlot(gameBoard,tmp) != NOT_HIGHLIGHTED){
                possibleLocations.push_back(tmp);
            }
        }
        //back bottom right
        tmp = Vector2i(slotPos.x - 2 , slotPos.y + 1);
        if(tmp.x  >= 0 && tmp.y < ChessBoard::BOARD_WIDTH){
            if(_canHighlightSlot(gameBoard,tmp) != NOT_HIGHLIGHTED){
                possibleLocations.push_back(tmp);
            }
        }
        return possibleLocations;
    }

    //shows possible move location of where the piece could move to
    void Knight::showPossibleMoveLocation(ChessBoard& gameBoard)const{
        std::vector<sf::Vector2i> possibleLocation = getPossibleMoveLocation(gameBoard);
        for(int i = 0; i < possibleLocation.size(); ++i){
            const sf::Vector2i& vec = possibleLocation[i];
            gameBoard.makeHighlighted(vec.x, vec.y);
        }
    }
    
}