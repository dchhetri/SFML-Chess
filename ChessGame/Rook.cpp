//
//  Rook.cpp
//  ChessGame
//
//  Created by Dibash Chhetri on 1/15/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#include "Rook.h"
#include "ChessPieceImageManager.h"

namespace ChessGame 
{
    Rook::Rook(detail::IChessPieceEnums::PieceId color ){
        m_pieceType = ROOK;
        m_sprite.SetImage(ChessPieceImageManager::getChessPieceImage(ROOK, color));
        m_pieceId = color;
    }
    
    //draws the chess piece
    void Rook::draw(sf::RenderWindow& canvas)const{
        canvas.Draw(m_sprite);
    }
    
    //moves the chess piece to the new location
    void Rook::animateTo(const sf::Vector2f& offsetPosition){
        m_sprite.Move(offsetPosition);
    }
    
    //returns the possible move location in ChessBoard::BoardSlot position
    std::vector<sf::Vector2i> Rook::getPossibleMoveLocation(ChessBoard& gameBoard)const{
        using sf::Vector2i;
        std::vector<sf::Vector2i> possibleLocations;

        Vector2i spritePos( int(m_sprite.GetPosition().x),int(m_sprite.GetPosition().y));
        Vector2i slotPos = gameBoard.convertToBoardIndex(spritePos.x,spritePos.y);
        
        if(slotPos == ChessBoard::BAD_INDEX) return possibleLocations;
        
        //check north squares
        Vector2i tmp(slotPos.x - 1, slotPos.y );
        while(tmp.x >= 0){
            HighlightedStatus status = _canHighlightSlot(gameBoard, tmp);
            if(status == EMPTY_SLOT_HIGHLIGHTED ){
                possibleLocations.push_back(tmp);
                tmp += Vector2i(-1,0); 
            }
            else if(status == ENEMY_SLOT_HIGHLIGHTED){
                possibleLocations.push_back(tmp);
                break;
            }
            else break;
        }
        //check south squares
        tmp = Vector2i(slotPos.x + 1, slotPos.y );
        while(tmp.x < ChessBoard::BOARD_HEIGHT){
            HighlightedStatus status = _canHighlightSlot(gameBoard, tmp);
            if(status == EMPTY_SLOT_HIGHLIGHTED ){
                possibleLocations.push_back(tmp);
                tmp += Vector2i(1,0); 
            }
            else if(status == ENEMY_SLOT_HIGHLIGHTED){
                possibleLocations.push_back(tmp);
                break;
            }
            else break;
        }
        //check east squares
        tmp = Vector2i(slotPos.x , slotPos.y - 1);
        while(tmp.y >= 0){
            HighlightedStatus status = _canHighlightSlot(gameBoard, tmp);
            if(status == EMPTY_SLOT_HIGHLIGHTED ){
                possibleLocations.push_back(tmp);
                tmp += Vector2i(0,-1); 
            }
            else if(status == ENEMY_SLOT_HIGHLIGHTED){
                possibleLocations.push_back(tmp);
                break;
            }
            else break;
        }
        //check west squares
        tmp = Vector2i(slotPos.x , slotPos.y + 1);
        while(tmp.y < ChessBoard::BOARD_WIDTH){
            HighlightedStatus status = _canHighlightSlot(gameBoard, tmp);
            if(status == EMPTY_SLOT_HIGHLIGHTED ){
                possibleLocations.push_back(tmp);
                tmp += Vector2i(0,1); 
            }
            else if(status == ENEMY_SLOT_HIGHLIGHTED){
                possibleLocations.push_back(tmp);
                break;
            }
            else break;
        }
        return possibleLocations;
    }

    //shows possible move location of where the piece could move to
    void Rook::showPossibleMoveLocation(ChessBoard& gameBoard)const{
        std::vector<sf::Vector2i> possibleLocation = getPossibleMoveLocation(gameBoard);
        for(int i = 0; i < possibleLocation.size(); ++i){
            const sf::Vector2i& vec = possibleLocation[i];
            gameBoard.makeHighlighted(vec.x, vec.y);
        }

    }

}
