//
// Created by dede on 21/04/18.
//

#include <algorithm>
#include "Heuristique.hpp"
#include <Utils.hpp>

#ifndef PROJET_HEURISTIQUETRIEPJWJ_HPP
#define PROJET_HEURISTIQUETRIEPJWJ_HPP

class HeuristiqueTriePJWJ:
public Heuristique{
    void predict(Machine& m1, Machine& m2, const std::vector<Task>& tasks) const override {

        std::vector<Task> wtasks = tasks;

        // On trie les tâches selont l'ordre pj*wj décroissant
        std::sort(wtasks.begin(), wtasks.end(), [](Task a, Task b){
            return a.p*a.w < b.p*b.w;
        });

        putTaskOnMachine(m1, m2, wtasks);


        // On test si il y a un wait sur m1 et on décalle
        if (m1.isWaiting())
            m1.shiftTask(m1.sumWaitingTime());

        // On test si il y a un wait sur m2 et on décalle
        if (m2.isWaiting())
            m2.shiftTask(m2.sumWaitingTime());
    }
};

#endif //PROJET_HEURISTIQUETRIEPJWJ_HPP
