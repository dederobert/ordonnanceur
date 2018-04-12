//
// Created by dede on 09/04/18.
//

#ifndef PROJET_MACHINE_HPP
#define PROJET_MACHINE_HPP

#include <vector>
#include <sstream>
#include "task.hpp"
/**
 * Défénie une machine
 */
class Machine {
public:
    // Date à laquelle la machine commence
    int start;
    // Date de fin des toutes les tâches qui sont placé sur la machine
    int end;
    // Somme des date de fin pondéré
    int sumCjWj;

    // Listes des tâches de la machine
    std::vector<Task> tasks{};

    /**
     * Constructeur par defaut
     */
    Machine():start(0),end(0),sumCjWj(0) {}

    /**
     * Ajoute une tâche à la machine
     * MAJ la date de fin et la somme
     * @param task Tâche à ajouter
     * @return elle-même
     */
    Machine& operator+(const Task& task) {
        tasks.push_back(task);
        end += task.p;
        sumCjWj += task.w*end;
        return *this;
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << "machine[start:" << start << ",end:" << end << ",sumCjWj:"<< sumCjWj << "]tasks{" << std::endl;
        for (auto t:tasks)
            oss << "\t" << t << std::endl;
        oss << "}";
        return oss.str();
    }

    friend std::ostream& operator<<(std::ostream& flux, const Machine& machine) {
        return flux << machine.toString();
    }
};
#endif //PROJET_MACHINE_HPP
