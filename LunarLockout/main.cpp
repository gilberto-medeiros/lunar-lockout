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
#include "IdCache.h"


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
        /*printLine("");
        printLine("startGrid");
        grid->printMoves();
        grid->print();*/
        std::list<Grid*> tmpMoves = grid->computeAllMoves();
        /*for (auto ogrid : tmpMoves) {
            ogrid->printMoves();
            ogrid->print();
        }*/
        endMoves.splice(endMoves.end(), tmpMoves);
    }
    
    return endMoves;
}

std::list<Grid*> findMinimalSolutions(Grid *igrid, int abortDepth) {
    std::list<Grid*> ret;
    
    Grid *g = new Grid(*igrid);
    std::list<Grid*> startGrids;
    startGrids.push_back(g);
    
    printLine("findMinimalSolution");
    g->print();
    
    int moveCount = 1;
    bool currentGridSolutionFound = false;
    while (!currentGridSolutionFound) {
        std::list<Grid*> moves = computeAllMoves(startGrids);
        
        auto it = moves.begin();
        while (it != moves.end()) {
            Grid *grid = *it;
            std::string sol = grid->buildMoveString();
            if (sol == "3R 2D 3L 0L ") {
                int i=0;
            }
            
            if (grid->isSolution()) {
                ret.push_back(grid);
                currentGridSolutionFound = true;
                // move element to end list
                it = moves.erase(it);
            }
            else {
                it++;
            }
        }
        
        for (auto grid : startGrids) {
            delete grid;
        }
        
        if (moves.size() == 0) {
            printLine("Search ended with no solutions");
            Analytics::reportEvent("Search ended with no solutions");
            break;
        }
        
        if ((ret.size() > 0)) {
            for (auto grid : moves) {
                delete grid;
            }
            
            printLine("returning " + std::to_string(ret.size()) + " solutions with " + std::to_string(moveCount) + " moves");
            Analytics::reportEvent("Solutions found");
            break;
        }
        
        //startGrids.splice(startGrids.end(), moves); - crashes?
        startGrids = moves;
        moveCount++;
        
        if ((moveCount >= abortDepth)) {
            for (auto grid : startGrids) {
                delete grid;
            }
            printLine("Search aborted due to depth");
            Analytics::reportEvent("Search aborted due to depth");
            break;
        }
    }
    
    return ret;
}

void findGridWithMinimalSolution(int numberOfBots, int numberOfMoves) {
    std::list<Piece*> pieces;
    for (int i= 0; i < numberOfBots; i++) {
        pieces.push_back(new Piece(i==0, i));
    }
    
    GridFactory::initialiseWithNumberOfPieces(numberOfBots);
    
    bool gridFound = false;
    do {
        IdCache::clear(); // cache has to be cleared because moves with solutions can be discarded
        Grid *g = GridFactory::createGrid(pieces);
        if (g == NULL) {
            printLine("No solution for bots: " + std::to_string(numberOfBots) + " moves: " + std::to_string(numberOfMoves));
            break;
        }
        if (!IdCache::reserveId(g->calculateId()) || g->isSolution()) {
            delete g;
            continue;
        }
        Analytics::reportEvent("Starting Grid Randomized");
        
        std::list<Grid*> solutions = findMinimalSolutions(g, numberOfMoves+1);
        
        bool isFirst = true;
        for (Grid* solution : solutions) {
            if (isFirst) {
                printLine("");
                g->print();
                if (solution->getMoveCount() == numberOfMoves) {
                    Analytics::reportEvent("Solutions with correct size");
                    printLine("FOUND " + std::to_string(solutions.size()) + " SOLUTIONs with " + std::to_string(numberOfMoves) + " moves");
                    gridFound = true;
                }
                else {
                    Analytics::reportEvent("solution too short");
                    printLine("short Solutions with " + std::to_string(solution->getMoveCount()) + " moves");
                }
                isFirst = false;
            }
            printLine("");
            g->print();
            solution->printMoves();
            solution->print();
        }
        
        for (auto grid : solutions) {
            delete grid;
        }
    } while (!gridFound);
    
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
