//
// Created by dede on 09/04/18.
//

#ifndef PROJET_HEURISTIQUE_HPP
#define PROJET_HEURISTIQUE_HPP

#include "../struct/Machine.hpp"

// Classe générique pour les heuristiques
class Heuristique {
public:
    // DP template methode
    virtual void predict(Machine& m1, Machine& m2, const std::vector<Task>& tasks) const = 0;
};

#endif //PROJET_HEURISTIQUE_HPP
