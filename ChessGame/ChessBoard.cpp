//
//  ChessBoard.cpp
//  ChessGame
//
//  Created by Dibash Chhetri on 1/9/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#include "ChessBoard.h"
#include "ChessPieceImageManager.h"
#include <cassert>
#include <iostream>
using namespace std;

namespace ChessGame 
{
    
    const sf::Vector2i ChessBoard::BAD_INDEX = sf::Vector2i(-1,-1);
    
    ChessBoard::ChessBoard(): m_position(200,100){
        _initialize();
    }
    
    //draws the board given canvas
    void ChessBoard::draw(sf::RenderWindow& canvas)const
    {
        //draw chess board
        for(int i = 0; i < m_board.size(); ++i){
            for(int j = 0; j < m_board.size(); ++j){
               //note we need to draw pieces first because of the draw ordering by sfml
                if(m_board[i][j].piece.get() != NULL){
                    m_board[i][j].piece->draw(canvas);
                }
                canvas.Draw( m_board[i][j].rect );
            }
        }
         //draw background
        canvas.Draw(m_background);
    }
    
    //returns the top left corner of the board
    sf::Vector2f ChessBoard::getPosition()const{
        return m_position;
    }
    
    
    //move piece to new location
    //if the new slot contains piece, it will get devoured and eaten    
    void ChessBoard::moveChessPiece(BoardSlot& oldSlot, BoardSlot& newSlot){
        //clear highlighted Entries        
        clearHighlightedEntries();
        
        
       //update newSlot piece
        newSlot.piece = oldSlot.piece;
        newSlot.status = OCCUPIED;
        //update the sprite's position
        newSlot.piece->setPosition( newSlot.rect.GetPosition());
        newSlot.piece->getSprite().Move(_calculateSpriteOffset(),_calculateSpriteOffset());
        //reset old slot
        oldSlot.piece = PiecePtr();
        oldSlot.status = EMPTY;
        
    }
    
    void ChessBoard::makeHighlighted(int row, int col){
        //save index
        m_highlightedList.push_back(sf::Vector2i(row,col));
        //change status
        m_board[row][col].status = HIGHLIGHTED;
        //show highlighted section
        m_board[row][col].rect.SetColor(sf::Color(175,111,54));
    }
    
    void ChessBoard::clearHighlightedEntries(){
        //clear highlighted list and set original color
        for(int i = 0; i < m_highlightedList.size(); ++i){
            sf::Vector2i pos = m_highlightedList[i];
            m_board[pos.x][pos.y].status = EMPTY;
            if( (pos.x + pos.y ) % 2 == 0) 
                m_board[pos.x][pos.y].rect.SetColor(sf::Color(111,111,111));
            else m_board[pos.x][pos.y].rect.SetColor(sf::Color(150,150,150));
        }
        m_highlightedList.clear();
    }
    
    
    //returns the constant slot in position (x,y)
    const ChessBoard::BoardSlot& ChessBoard::getSlot(int row, int col)const{
        return m_board[row][col];   
    }
    //returns the slot in position (x,y)
    ChessBoard::BoardSlot& ChessBoard::getSlot(int row, int col){
        return m_board[row][col];
    }
    
    //returns true if current slot is occupied
    bool ChessBoard::isOccupied(int row, int col)const{
        return m_board[row][col].status == OCCUPIED;
    }
    //returns true if slot is occupied with enemey
    bool ChessBoard::isOccupiedWithEnemy(int row, int col,const detail::IChessPieceEnums::PieceId& pieceId){
        return  isOccupied(row, col) && m_board[row][col].piece->getPieceID() != pieceId;
    }
    //repositions the pieces to its initial position
    void ChessBoard::reset(){
        populate(m_whitePieceSet, m_blackPieceSet);
    }
    
    //returns true if the window  coordinates is inside the board
    bool ChessBoard::contains(int winX, int winY)const{
        return  winX > m_position.x && winX < m_position.x + BOARD_WIDTH * CELL_SIZE
                && winY > m_position.y && winY < m_position.y + BOARD_WIDTH * CELL_SIZE;
    }

    sf::Vector2i ChessBoard::convertToBoardIndex(int winX, int winY)const{
        //if not within bounds return bad index
        if(!contains(winX,winY)){
            return BAD_INDEX;
        }
        else{
            //else calculate and return index
            return sf::Vector2i((winY - m_position.y)/CELL_SIZE,(winX - m_position.x)/CELL_SIZE);
        }
    }
    
    //positions the two set of pieces to its initial start position
    void ChessBoard::populate(PieceSet& set1, PieceSet& set2)
    {
        assert(set1.size() == set2.size() && "Error: both set has to have equal size");
        //save pieces
        m_whitePieceSet = set1;
        m_blackPieceSet = set2;
        
        const int MAX_PIECES_PER_ROW = 8;
        const int penultimateRowIndex = BOARD_HEIGHT - 2; //second last board index
        const int nRow = int(set1.size()/MAX_PIECES_PER_ROW);
        const float offset = _calculateSpriteOffset();
        //set the pieces on the board properly
        for(int i = 0; i < nRow; ++i)
        {
            for(int j = 0; j < MAX_PIECES_PER_ROW; ++j)
            {
                const int transformedIndex = MAX_PIECES_PER_ROW * i + j;
                //set piece and proper location
                m_board[i][j].piece = set1[transformedIndex];
                m_board[i][j].piece->setPosition( m_board[i][j].rect.GetPosition());
                m_board[i][j].piece->getSprite().Move(sf::Vector2f(offset,offset));
                m_board[i][j].piece->getSprite().Resize(SPRITE_SIZE,SPRITE_SIZE);
                m_board[i][j].status = OCCUPIED;
                m_board[i][j].piece->setPieceDirection(IChessPiece::UP);
                m_board[i][j].piece->setPieceID(IChessPiece::WHITE_PIECE_ID);
                
                //set piece and proper location
                m_board[i + penultimateRowIndex][j].piece = set2[transformedIndex];
                m_board[i + penultimateRowIndex][j].piece->setPosition( m_board[i+penultimateRowIndex][j].rect.GetPosition());
                m_board[i + penultimateRowIndex][j].piece->getSprite().Resize(SPRITE_SIZE,SPRITE_SIZE);;
                m_board[i + penultimateRowIndex][j].piece->getSprite().Move(sf::Vector2f(offset,offset));
                m_board[i + penultimateRowIndex][j].status = OCCUPIED;
                m_board[i + penultimateRowIndex][j].piece->setPieceDirection(IChessPiece::DOWN);
                m_board[i + penultimateRowIndex][j].piece->setPieceID(IChessPiece::BLACK_PIECE_ID);
            }
        }
        
    }
    
    /*** private helper functions ***/
    //initializes an empty board
    void ChessBoard::_initialize()
    {
        for(int i = 0; i < m_board.size(); ++i)
        {
            for(int j = 0; j < m_board.size(); ++j)
            {
                //alternate color between black and white
                if( (i + j) % 2 == 0){
                    m_board[i][j].rect.SetColor(sf::Color(111,111,111));
                }else{
                    m_board[i][j].rect.SetColor(sf::Color(150,150,150));
                }
                //set proper position
                m_board[i][j].rect.SetPosition(CELL_SIZE*j + m_position.x, CELL_SIZE*i + m_position.y);
                m_board[i][j].rect.Resize(CELL_SIZE,CELL_SIZE);
                m_board[i][j].status = EMPTY;
                
            }
        }
        
        //setup backgroud
        const int BORDER_WIDTH = 50;
        m_background.SetColor(sf::Color(90,90,90));
        m_background.Resize(400 + BORDER_WIDTH, 400 + BORDER_WIDTH);
        m_background.Move(200 - BORDER_WIDTH/2, 100 - BORDER_WIDTH/2);
    }

    float ChessBoard::_calculateSpriteOffset()const{
        return (CELL_SIZE - SPRITE_SIZE)/2.0f;
    }
    
    
}