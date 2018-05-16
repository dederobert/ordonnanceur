//
// Created by dede on 16/05/18.
//

#ifndef PROJET_GENETIQUEORDRETACHE_HPP
#define PROJET_GENETIQUEORDRETACHE_HPP

#include <cstdlib>
#include <ctime>
#include "GenetiqueOld.hpp"

template<typename T>
class Genetique {
public:
    Chromosome<T> *cross(Chromosome<T> c1, Chromosome<T> c2) const {
        Chromosome<T> *c = new Chromosome<int>();
        bool found = false;
        int i, j = 0;
        for (i = 0; i < c1.size() / 2; i++)
            *c = *c + c1[i];

        for (; i < c1.size();) {
            for (int k = 0; k < i; k++)
                if (c2[j] == (*c)[k]) {
                    j++;
                    found = true;
                    break;
                }
            if (!found) {
                *c = *c + c2[j++];
                i++;
            }
            found = false;
        }
        return c;
    }

    Chromosome<T> *mutation(Chromosome<T> c) const {
        Chromosome<T> *cp = new Chromosome<T>(c);
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        int random1, random2;

        do {
            random1 = std::rand();
            random2 = std::rand();
            random1 = static_cast<int>(random1 / static_cast<double>(RAND_MAX) * c.size());
            random2 = static_cast<int>(random2 / static_cast<double>(RAND_MAX) * c.size());
        } while (random1 == random2);

        cp->permute(random1, random2);
        return cp;
    }
};
template<typename T>
std::vector<Task> Chromosome2Tasks(const Chromosome<T> &c, const std::vector<Task> &tasks) {
    std::vector<Task> res;
    for (int i = 0; i < c.size(); i++)
        res.push_back(tasks[c[i]]);
    return res;
}
template<typename T>
int evaluateChromosome(const Chromosome<T>& c, std::vector<Task> tasks){
    Machine mg1, mg2;
    putTaskOnMachine(mg1, mg2, Chromosome2Tasks(c, tasks));
    // On test si il y a un wait sur m1 et on décalle
    if (mg1.isWaiting())
        mg1.shiftTask(mg1.sumWaitingTime());

    // On test si il y a un wait sur m2 et on décalle
    if (mg2.isWaiting())
        mg2.shiftTask(mg2.sumWaitingTime());

    if (mg1.sumCjWj > mg2.sumCjWj)
        return mg1.sumCjWj;
    return mg2.sumCjWj;
}


#endif //PROJET_GENETIQUEORDRETACHE_HPP
