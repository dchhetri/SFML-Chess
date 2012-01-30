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
#include <iostream>
#include <string>
using namespace std;

namespace ChessGame 
{

    //static variable initialization
    ChessPieceImageManager::ChessPieceList ChessPieceImageManager::imageList;
    
    
    //static functions

    void ChessPieceImageManager::initialize(){
        const string base = "/Users/MacBoss/Documents/XCodeWorkspace/ChessGame/ChessGame/";
        using namespace detail;
        //load in pawn image
<<<<<<< HEAD
        assert( imageList[PAWN].LoadFromFile("/Users/MacBoss/Desktop/white_pawn.png") && "Error: Could not Load Pawn");
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
    
=======
        assert( imageList[IChessPieceEnums::PAWN][IChessPieceEnums::WHITE_PIECE_ID].LoadFromFile(base + "whitePawn.png") 
                && "Error: Could not Load white Pawn");
        assert( imageList[IChessPieceEnums::KNIGHT][IChessPieceEnums::WHITE_PIECE_ID].LoadFromFile(base + "whiteKnight.png")
                && "Error: Could not Load white Knight");
        assert( imageList[IChessPieceEnums::BISHOP][IChessPieceEnums::WHITE_PIECE_ID].LoadFromFile(base + "whiteBishop.png") 
                && "Error: Could not Load white Bishop");
        assert( imageList[IChessPieceEnums::ROOK][IChessPieceEnums::WHITE_PIECE_ID].LoadFromFile(base + "whiteRook.png") 
                && "Error: Could not Load white Rook");        
        assert( imageList[IChessPieceEnums::QUEEN][IChessPieceEnums::WHITE_PIECE_ID].LoadFromFile(base + "whiteQueen.png") 
                && "Error: Could not Load white Queen");                
        assert( imageList[IChessPieceEnums::KING][IChessPieceEnums::WHITE_PIECE_ID].LoadFromFile(base + "whiteKing.png") 
                && "Error: Could not Load white King");                
        
        assert( imageList[IChessPieceEnums::PAWN][IChessPieceEnums::BLACK_PIECE_ID].LoadFromFile(base + "blackPawn.png") 
                && "Error: Could not Load black Pawn");
        assert( imageList[IChessPieceEnums::KNIGHT][IChessPieceEnums::BLACK_PIECE_ID].LoadFromFile(base + "blackKnight.png") 
                && "Error: Could not Load black Knight");
        assert( imageList[IChessPieceEnums::BISHOP][IChessPieceEnums::BLACK_PIECE_ID].LoadFromFile(base + "blackBishop.png") 
                && "Error: Could not Load black Bishop");
        assert( imageList[IChessPieceEnums::ROOK][IChessPieceEnums::BLACK_PIECE_ID].LoadFromFile(base + "blackRook.png") 
                && "Error: Could not Load black Rook");        
        assert( imageList[IChessPieceEnums::QUEEN][IChessPieceEnums::BLACK_PIECE_ID].LoadFromFile(base + "blackQueen.png") 
                && "Error: Could not Load black Queen");                
        assert( imageList[IChessPieceEnums::KING][IChessPieceEnums::BLACK_PIECE_ID].LoadFromFile(base + "blackKing.png") 
                && "Error: Could not Load black King");  
        
    }
    //returns the specified piece 
    const sf::Image& ChessPieceImageManager::getChessPieceImage(detail::IChessPieceEnums::PieceType type,
                                                                detail::IChessPieceEnums::PieceId color){
        return imageList[type][color];
    }
        
>>>>>>> developing_branch
}
