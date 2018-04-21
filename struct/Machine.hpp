//
// Created by dede on 09/04/18.
//

#ifndef PROJET_MACHINE_HPP
#define PROJET_MACHINE_HPP

#include <vector>
#include <sstream>
#include <tuple>
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
    std::vector<std::tuple<int, int ,Task>> tasks{};

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
        int taskStartDate = (task.r >= end)? task.r:end;
        std::tuple<int, int, Task> ttask(taskStartDate,taskStartDate+task.p, task);
        tasks.push_back(ttask);
        end += taskStartDate+task.p;
        sumCjWj += task.w*end;
        return *this;
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << "machine[start:" << start << ",end:" << end << ",sumCjWj:"<< sumCjWj << "]tasks{" << std::endl;
        int startTask, endTask;
        Task ts;
        for (auto t:tasks) {
            oss << "\t" << std::get<2>(t) << std::endl;
        }
        oss << "}";
        return oss.str();
    }

    friend std::ostream& operator<<(std::ostream& flux, const Machine& machine) {
        return flux << machine.toString();
    }

    bool isWaiting() const {
        return maxWaitingTime()!=0;
    }

    unsigned int maxWaitingTime() const{
        int maxWaiting = 0;
        int precedentEnd = std::get<1>(tasks.front());
        bool firstTask = true;
        for (auto t:tasks) {
            // On ne test pas la premiere tache
            if (firstTask) {firstTask = false;continue;}
            // Si la date de debut de la tâche est différent de la date de fin de la tache précedente
            if (precedentEnd != std::get<0>(t))
                maxWaiting = (std::get<0>(t) - precedentEnd);
            precedentEnd = std::get<1>(t);
        }
        return maxWaiting;
    }

    void shiftTask(unsigned int shift) {
        // On save les taches
        std::vector<std::tuple<int, int ,Task>> tmp = tasks;
        tasks.clear();

        // On décale la date de début et initialise la date de fin
        start += shift;
        end = shift;

        // On replace toutes les tâches
        for (auto t: tmp)
            *this = *this + std::get<2>(t);
    }
};
#endif //PROJET_MACHINE_HPP
