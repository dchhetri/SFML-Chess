//
//  ChessPieceImageManager.cpp
//  ChessGame
//
//  Created by Dibash Chhetri on 1/9/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#include "ChessPieceImageManager.h"
#include "ChessPiece.h"

#include <cassert>
namespace ChessGame 
{

    //static variable initialization
    ChessPieceImageManager::ChessPieceList ChessPieceImageManager::imageList;
    
    
    //static functions

    void ChessPieceImageManager::initialize(){
        //load in pawn image
        assert( imageList[PAWN].LoadFromFile("../Images/white_pawn.png") && "Error: Could not Load Pawn");
        assert( imageList[KNIGHT].LoadFromFile("/Users/MacBoss/Desktop/white_knight.png") && "Error: Could not Load Knight");
        assert( imageList[BISHOP].LoadFromFile("/Users/MacBoss/Desktop/white_bishop.png") && "Error: Could not Load Bishop");
        assert( imageList[ROOK].LoadFromFile("/Users/MacBoss/Desktop/white_rook.png") && "Error: Could not Load Rook");        
        assert( imageList[QUEEN].LoadFromFile("/Users/MacBoss/Desktop/white_queen.png") && "Error: Could not Load Queen");                
        assert( imageList[KING].LoadFromFile("/Users/MacBoss/Desktop/white_king.png") && "Error: Could not Load King");                
    }
    
    const sf::Image& ChessPieceImageManager::getPawnImage(){
        return imageList[PAWN];
    }
    const sf::Image& ChessPieceImageManager::getKnightImage(){
        return imageList[KNIGHT];
    }
    const sf::Image& ChessPieceImageManager::getBishopImage(){
        return imageList[BISHOP];
    }
    const sf::Image& ChessPieceImageManager::getRookImage(){
        return imageList[ROOK];
    }
    const sf::Image& ChessPieceImageManager::getQueenImage(){
        return imageList[QUEEN];
    }
    const sf::Image& ChessPieceImageManager::getKingImage(){
        return imageList[KING];
    }
    const sf::Image& ChessPieceImageManager::getChessGameBackgroundImage(){
        return imageList[BACKGROUND_IMAGE];
    }
    
}
