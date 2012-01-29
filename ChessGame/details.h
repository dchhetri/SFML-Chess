//
//  details.h
//  ChessGame
//
//  Created by Dibash Chhetri on 1/14/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#ifndef ChessGame_details_h
#define ChessGame_details_h


#include <SFML/Graphics/Sprite.hpp>

namespace ChessGame 
{
    
    namespace detail
    {
        class IChessPieceEnums
        {
        public:
            enum PieceType{PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};
            enum PieceDirection{ UP = 1 , DOWN  = -1};
            enum PieceId{ WHITE_PIECE_ID, BLACK_PIECE_ID };
        };
        
    };
    
}
#endif
