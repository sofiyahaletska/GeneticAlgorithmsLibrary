#include "genetic.h"

std::vector<std::string>* Genetic::childSinglePoint(std::vector<std::string>* binary_p1, std::vector<std::string>* binary_p2){
    auto child = new std::vector<std::string>();
    for(int i = 0; i < binary_p1->size(); i++){
        for(int j = 0; j < (*binary_p1)[i].size()/2; j++) {
            std::string s(1, (*binary_p1)[i][j]);
            child->push_back(s);
        }
        for(int l = (*binary_p2)[i].size()/2; l < (*binary_p2)[i].size(); l++) {
            std::string x(1, (*binary_p2)[i][l]);
            child->push_back(x);
        }
    }
    return child;
}

std::vector<std::string>* Genetic::childSemirandomBit(std::vector<std::string>* binary_p1, std::vector<std::string>* binary_p2){
    auto child = new std::vector<std::string>();
    for(int i = 0; i < binary_p1->size(); i++){
        for(int j = 0; j < (*binary_p1)[i].size(); j++){
            if ((*binary_p1)[i][j] == (*binary_p2)[i][j]){
                std::string s(1, (*binary_p1)[i][j]);
                child->push_back(s);
            } else {
                int rand = getRand(0, 1);
                child->push_back(std::to_string(rand));
            }

        }
    }
    return child;
}