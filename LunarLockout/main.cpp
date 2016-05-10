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
        printLine("");
        printLine("startGrid");
        grid->print();
        std::list<Grid*> tmpMoves = grid->computeAllMoves();
        for (auto ogrid : tmpMoves) {
            ogrid->printMoves();
            ogrid->print();
        }
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
    bool currentGridSolutionFound = false;
    do {
        Grid *g = GridFactory::createGrid(pieces);
        if (g == NULL) {
            printLine("No solution for bots: " + std::to_string(numberOfBots) + " moves: " + std::to_string(numberOfMoves));
            break;
        }
        if (g->isSolution()) {
            delete g;
            continue;
        }
        Grid initialGridBackup(*g);
        //g->print();
        std::list<Grid*> startGrids;
        startGrids.push_back(g);
        
        int moveCount = 0;
        currentGridSolutionFound = false;
        while (!currentGridSolutionFound) {
            std::list<Grid*> moves = computeAllMoves(startGrids);
            
            for (auto grid: moves) {
                std::string sol = grid->buildMoveString();
                if (sol == "3R 2D 3L 0L") {
                    int i=0;
                }
                
                if (grid->isSolution()) {
                    solutionFound = (moveCount+1) == numberOfMoves;
                    currentGridSolutionFound = true;
                    
                    if ((moveCount+1) == numberOfMoves) {
                        printLine("");
                        initialGridBackup.print();
                        printLine("FOUND SOLUTION with " + std::to_string(moveCount+1) + " moves");
                        grid->printMoves();
                        grid->print();
                    }
                    else {
                        Analytics::reportEvent("solution too short");
                        printLine("Solution with " + std::to_string(moveCount) + " moves");
                        grid->printMoves();
                        grid->print();
                    }
                }
            }
            
            for (auto grid : startGrids) {
                delete grid;
            }
            
            startGrids = moves;
            moveCount++;
            
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
                Analytics::reportEvent("stopping due to depth too high");
                //printLine("stopping due to depth");
                break;
            }
        }
        Analytics::reportEvent("starting grids");
        //printLine("startGrids = " + std::to_string(startGridCount));
    } while (!solutionFound && !currentGridSolutionFound);
    
    for (auto piece : pieces) {
        delete piece;
    }
}


int main(int argc, const char * argv[]) {
    int numberOfBots, numberOfMoves;
    if (validateArguments(argc, argv, numberOfBots, numberOfMoves)) {
        
        findGridWithMinimalSolution(6, 5); Analytics::dashboard();
        
        /*for (int pieces = 2; pieces < 7; pieces++) {
            for (int moves=2; moves < 10; moves++) {
                printLine("");
                printLine("attempt " + std::to_string(pieces) + " moves: " + std::to_string(moves));
                findGridWithMinimalSolution(pieces, moves);
            }
        }Analytics::dashboard();*/
        
        
        
        int i=0;
    }
    
    return 0;
}
