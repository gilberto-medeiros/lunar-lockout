//
//  main.cpp
//  LunarLockout
//
//  Created by Gilberto Medeiros on 06/05/16.
//  Copyright (c) 2016 Gilberto Medeiros. All rights reserved.
//

#include <iostream>
#include <string>
#include "Grid.h"
#include "Piece.h"


void printLine(const std::string &line) {
    std::cout << line << std::endl;
}

bool validateArguments(int argc, const char * argv[], int &numberOfBots, int &numberOfMoves) {
    if (argc < 2) {
        printLine("Not enough arguments");
        exit(-1);
    }
    
    // dbg
    numberOfBots = 5;
    numberOfMoves = 4;
    
    return true;
}

std::list<Grid*> computeAllMoves(std::list<Grid*> startGrids) {
    std::list<Grid*> endMoves;
    for (auto grid : startGrids) {
        std::list<Grid*> tmpMoves = grid->computeAllMoves();
        endMoves.splice(endMoves.end(), tmpMoves);
    }
    
    return endMoves;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printLine("HelloWorld");
    
    int numberOfBots, numberOfMoves;
    if (validateArguments(argc, argv, numberOfBots, numberOfMoves)) {
        std::list<Piece*> pieces;
        for (int i= 0; i < numberOfBots; i++) {
            pieces.push_back(new Piece(i==0));
        }
        
        Grid *g = new Grid(pieces);
        
        std::list<Grid*> startGrids;
        startGrids.push_back(g);
        
        int moveCount = 0;
        while (true) {
            std::list<Grid*> moves = computeAllMoves(startGrids);
            
            if (moves.size() == 0) {
                break;
            }
            
            for (auto grid: moves) {
                grid->print();
                if (grid->isSolution()) {
                    printLine("FOUND SOLUTION with " + std::to_string(moveCount+1) + " moves");
                }
                printLine("----------");
            }
            
            printLine("----------");
            startGrids = moves;
            moveCount++;
        }
 
        
        
        int i=0;
    }
    
    return 0;
}
