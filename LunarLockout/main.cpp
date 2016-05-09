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
#include "GridFactory.h"


void printLine(const std::string &line) {
    std::cout << line << std::endl;
}

bool validateArguments(int argc, const char * argv[], int &numberOfBots, int &numberOfMoves) {
    if (argc < 2) {
        printLine("Not enough arguments");
        exit(-1);
    }
    
    // dbg
    
    numberOfBots = std::stoi(argv[1]);
    numberOfMoves = std::stoi(argv[2]);
    
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

void findGridWithMinimalSolution(int numberOfBots, int numberOfMoves) {
    std::list<Piece*> pieces;
    for (int i= 0; i < numberOfBots; i++) {
        pieces.push_back(new Piece(i==0, i));
    }
    
    GridFactory::initialiseWithNumberOfPieces(numberOfBots);
    
    bool solutionFound = false;
    int startGridCount = 1;
    do {
        Grid *g = GridFactory::createGrid(pieces);
        if (g == NULL) {
            printLine("No solution for bots: " + std::to_string(numberOfBots) + " moves: " + std::to_string(numberOfMoves));
            break;
        }
        //g->print();
        std::list<Grid*> startGrids;
        startGrids.push_back(g);
        
        int moveCount = 0;
        while (!solutionFound) {
            std::list<Grid*> moves = computeAllMoves(startGrids);
            
            for (auto grid: moves) {
                if (grid->isSolution()) {
                    //printLine("FOUND SOLUTION with " + std::to_string(moveCount+1) + " moves");
                    solutionFound = (moveCount+1) == numberOfMoves;
                }
            }
            
            for (auto grid : startGrids) {
                delete grid;
            }
            
            startGrids = moves;
            moveCount++;
            //printLine("depth = " + std::to_string(moveCount));
            
            if (moves.size() == 0) {
                for (auto grid : moves) {
                    delete grid;
                }
                Analytics::reportEvent("no more moves");
                //printLine("no more moves");
                break;
            }
            
            if (!solutionFound && moveCount >= numberOfMoves) {
                for (auto grid : startGrids) {
                    delete grid;
                }
                Analytics::reportEvent("stopping due to depth");
                //printLine("stopping due to depth");
                break;
            }
        }
        startGridCount++;
        //printLine("startGrids = " + std::to_string(startGridCount));
    } while (!solutionFound);
    
    for (auto piece : pieces) {
        delete piece;
    }
}


int main(int argc, const char * argv[]) {
    int numberOfBots, numberOfMoves;
    if (validateArguments(argc, argv, numberOfBots, numberOfMoves)) {
        
        //findGridWithMinimalSolution(2, 2); Analytics::dashboard();
        
        for (int pieces = 2; pieces < 7; pieces++) {
            for (int moves=2; moves < 10; moves++) {
                printLine("");
                printLine("attempt " + std::to_string(pieces) + " moves: " + std::to_string(moves));
                findGridWithMinimalSolution(pieces, moves);
            }
        }
        
        
        Analytics::dashboard();
        int i=0;
    }
    
    return 0;
}
