//
//  User.h
//  ChessGame
//
//  Created by Dibash Chhetri on 1/10/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#ifndef ChessGame_User_h
#define ChessGame_User_h

#include <string>

//represents a player in the game
struct User{
    std::string name;
    int id;
    User(const std::string& name = "user", int id = 0) : name(name), id(id){}
};

#endif
