#include "Opdracht4_2_Winners.hpp"

float averageOfVector(const vector<float>& scores){
    float total = 0;
    for (int i = 0; i < scores.size(); i++){
        total += scores[i];
    }
    return (total / scores.size());
}

float nearestScore2Average(const vector<float>& scores) {
    float average = averageOfVector(scores);
    float closest = scores[0];
    for(int i = 0; i < scores.size(); i++){
        if((fabsf(average - scores[i])) < (average - closest)){
            closest = scores[i];
        }
    }
    return closest;
}

float furthestScoreFromWinner(const vector<float>& scores) { 
    float furthest = 0;
    float average = averageOfVector(scores);
    for(int i = 0; i < scores.size(); i++){
        if((fabsf(average - scores[i])) > furthest){
            furthest = scores[i];
        }
    }
    return furthest;
}