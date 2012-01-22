//
//  SidePanel.h
//  ChessGame
//
//  Created by Dibash Chhetri on 1/17/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#ifndef ChessGame_SidePanel_h
#define ChessGame_SidePanel_h

#include <vector>
#include <boost/shared_ptr.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
using namespace std;

namespace ChessGame
{
    
    //A side panel to hold elements
    //Kind of like a table with the given width/height dimension to hold
    //a element in each slot, main intention is to be used to show the dead chess
    //pieces of the oppoenents'
    template<typename T, int HEIGHT, int WIDTH>
    class SidePanel{
    private:
        enum { CELL_SIZE = 45 };
       // typedef boost::shared_ptr<ElementType> ElementPtr;
        typedef T ElementType;
        struct PanelSlot{
            sf::Sprite sprite;
            ElementType piece;
            PanelSlot(){}
        };
        typedef boost::array<PanelSlot,WIDTH> RowType;
        typedef boost::array<RowType,HEIGHT> ElementList;
    private:
        ElementList  m_list;
        sf::Vector2f m_position;
        sf::Vector2i m_insertIndex;
        sf::Sprite   m_background;
    public:
        SidePanel(){
            _initialize();
        }
        
        //adds to the next open slot
        void addNext(ElementType& elem){  
            if(m_insertIndex.y < WIDTH){
                PanelSlot& slot = m_list[m_insertIndex.x][m_insertIndex.y];
                slot.piece = elem;
                //set appropriate position
                sf::Vector2f pos = slot.sprite.GetPosition();
                slot.piece->setPosition(pos);
                //check to see if we need to increase insert position
                if(++m_insertIndex.y >= WIDTH){
                    ++m_insertIndex.x;
                    m_insertIndex.y = 0;
                }
                
            }else if(m_insertIndex.x < HEIGHT){
                m_insertIndex.x++;
                m_insertIndex.y = 0;
                m_list[m_insertIndex.x][m_insertIndex.y].piece = elem;
            }else{
                /* error not enough slot */
            }
        }
        void remove(int row, int col){
            m_list[row][col] = ElementType();
        }
        
        void setPosition(const sf::Vector2f& position){
            m_position = position;
            for(int i = 0; i < HEIGHT; ++i){
                for(int j = 0; j < WIDTH; ++j){
                    m_list[i][j].sprite.Move(position);
                }
            }
            m_background.SetPosition(position);
        }
        sf::Vector2f getPosition()const{
            return m_position;
        }
        void setBackgoundColor(const sf::Color& col){
            m_background.SetColor(col);
        }
        void setCellColor(const sf::Color& col){
            for(int i = 0; i < HEIGHT; ++i){
                for(int j = 0; j < WIDTH; ++j){
                    m_list[i][j].sprite.SetColor(col);
                }
            }
        }
        sf::Color getCellColor()const{
            return m_list[0][0].sprite.GetColor();
        }
        sf::Color getBackgroundColor()const{
            return m_background.GetColor();
        }
        void draw(sf::RenderWindow& canvas)const{
            for(int i = 0; i < HEIGHT; ++i){
                for(int j = 0; j < WIDTH; ++j){
                    if(m_list[i][j].piece.get() != NULL){
                        m_list[i][j].piece->draw(canvas); 
                    }
                    canvas.Draw(m_list[i][j].sprite);
                }
            }
            canvas.Draw( m_background );
        }
        bool isFilled()const{
            return m_insertIndex.x == WIDTH && m_insertIndex.y == HEIGHT;
        }
        //private helper function
    private:
        void _initialize(){
            for(int i = 0; i < HEIGHT; ++i){
                for(int j = 0; j < WIDTH; ++j){
                    m_list[i][j].sprite.SetColor( sf::Color(123,123,123) );
                    m_list[i][j].sprite.Resize(CELL_SIZE - 10,CELL_SIZE - 10);
                    m_list[i][j].sprite.SetPosition(5 + i * CELL_SIZE, 5 + j * CELL_SIZE );
                }
            }
            m_background.SetColor(sf::Color(200,200,200));
            m_background.Resize((CELL_SIZE ) * HEIGHT, (CELL_SIZE ) * WIDTH);
        }
    };

}
#endif
