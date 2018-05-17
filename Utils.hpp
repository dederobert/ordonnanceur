//
// Created by dede on 16/05/18.
//

#ifndef PROJET_UTILS_HPP
#define PROJET_UTILS_HPP

#include "struct/Machine.hpp"
#include "genetique/Chromosome.hpp"

template<typename T>
T max(T v1, T v2) {
    if (v1 > v2)
        return v1;
    return v2;
}

void putTaskOnMachine(Machine& m1, Machine& m2,const std::vector<Task>& tasks) {
    // On place toutes les tâches
    for (Task task : tasks) {
        // On test la machine la moins chargé
        // A voir si on test sur end ou sumCjWJ
        if (m1.end <= m2.end)
            m1 = m1 + task;
        else
            m2 = m2 + task;
    }
}


#endif //PROJET_UTILS_HPP
