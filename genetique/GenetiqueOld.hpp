//
// Created by dede on 16/05/18.
//

#ifndef PROJET_GENETIQUE_HPP
#define PROJET_GENETIQUE_HPP

#include <vector>
#include "Chromosome.hpp"
#include <task.hpp>

template<typename T>
class GenetiqueOld {
public:
    // DP template methode
    virtual Chromosome<T>* cross(Chromosome<T> c1, Chromosome<T> c2) const =0;
    virtual Chromosome<T>* mutation(Chromosome<T> c) const = 0;
    virtual std::vector<Task> Chromosome2Tasks(const Chromosome<T>& c,const std::vector<Task>& tasks) const = 0;
    virtual int evaluateChromosome(const Chromosome<T>& c, std::vector<Task> tasks) const = 0;
};

#endif //PROJET_GENETIQUE_HPP
