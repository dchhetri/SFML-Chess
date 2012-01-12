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
        assert( imageList[PAWN].LoadFromFile("/Users/MacBoss/Desktop/white_pawn.png") && "Error: Could not Load Pawn");
       // assert( imageList[BACKGROUND_IMAGE].LoadFromFile("/Users/MacBoss/Desktop/Background2.jpg") && "Error: Could not Load background immage");
    }
    
    const sf::Image& ChessPieceImageManager::getPawnImage(){
        return imageList[PAWN];
    }
    const sf::Image& ChessPieceImageManager::getChessGameBackgroundImage(){
        return imageList[BACKGROUND_IMAGE];
    }
}
