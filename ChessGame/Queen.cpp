//
//  Queen.cpp
//  ChessGame
//
//  Created by Dibash Chhetri on 1/15/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#include "Queen.h"
#include "ChessPieceImageManager.h"

namespace ChessGame 
{
    Queen::Queen(detail::IChessPieceEnums::PieceId color ){
        m_pieceType = QUEEN;
        m_sprite.SetImage(ChessPieceImageManager::getChessPieceImage(QUEEN, color));        
        m_pieceId = color;
    }
    
    //draws the chess piece
    void Queen::draw(sf::RenderWindow& canvas)const{
        canvas.Draw(m_sprite);
    }
    
    //moves the chess piece to the new location
    void Queen::animateTo(const sf::Vector2f& offsetPosition){
        m_sprite.Move(offsetPosition);
    }
    
    //returns the possible move location in ChessBoard::BoardSlot position
    std::vector<sf::Vector2i> Queen::getPossibleMoveLocation(ChessBoard& gameBoard)const{
        std::vector<sf::Vector2i> possibleLocations;
        using sf::Vector2i;
        Vector2i spritePos( int(m_sprite.GetPosition().x),int(m_sprite.GetPosition().y));
        Vector2i slotPos = gameBoard.convertToBoardIndex(spritePos.x,spritePos.y);
        
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
        
        tmp = Vector2i(slotPos.x - 1, slotPos.y - 1);
        //check top left-diagnol if available
        while(tmp.x >= 0 && tmp.y >= 0)
        {   
            HighlightedStatus status = _canHighlightSlot(gameBoard, tmp);
            if(status == EMPTY_SLOT_HIGHLIGHTED ){
                possibleLocations.push_back(tmp);
                tmp += Vector2i(-1,-1); 
            }
            else if(status == ENEMY_SLOT_HIGHLIGHTED){
                possibleLocations.push_back(tmp);
                break;
            }
            else break; 
            
        }
        //check top right-diagnol
        tmp = Vector2i(slotPos.x - 1, slotPos.y + 1);
        while(tmp.x >= 0 && tmp.y < ChessBoard::BOARD_WIDTH){
            HighlightedStatus status = _canHighlightSlot(gameBoard, tmp);
            if(status == EMPTY_SLOT_HIGHLIGHTED ){
                possibleLocations.push_back(tmp);
                tmp += Vector2i(-1,1); 
            }
            else if(status == ENEMY_SLOT_HIGHLIGHTED){
                possibleLocations.push_back(tmp);
                break;
            }
            else break;
        }
        //check bottom left-diagnol
        tmp = Vector2i(slotPos.x + 1, slotPos.y - 1);
        while(tmp.x < ChessBoard::BOARD_HEIGHT && tmp.y >= 0){
            HighlightedStatus status = _canHighlightSlot(gameBoard, tmp);
            if(status == EMPTY_SLOT_HIGHLIGHTED ){
                possibleLocations.push_back(tmp);
                tmp += Vector2i(1,-1); 
            }
            else if(status == ENEMY_SLOT_HIGHLIGHTED){
                possibleLocations.push_back(tmp);
                break;
            }
            else break;
        }
        //check bottom right-diagnol
        tmp = Vector2i(slotPos.x + 1, slotPos.y + 1);
        while(tmp.x < ChessBoard::BOARD_HEIGHT && tmp.y < ChessBoard::BOARD_HEIGHT){
            HighlightedStatus status = _canHighlightSlot(gameBoard, tmp);
            if(status == EMPTY_SLOT_HIGHLIGHTED ){
                possibleLocations.push_back(tmp);
                tmp += Vector2i(1,1); 
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
    void Queen::showPossibleMoveLocation(ChessBoard& gameBoard)const{
        std::vector<sf::Vector2i> possibleLocation = getPossibleMoveLocation(gameBoard);
        for(int i = 0; i < possibleLocation.size(); ++i){
            const sf::Vector2i& vec = possibleLocation[i];
            gameBoard.makeHighlighted(vec.x, vec.y);
        }        
    }
    
}
