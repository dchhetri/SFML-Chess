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
        
}
