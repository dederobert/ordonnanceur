
#ifndef PROJET_TASK_HPP
#define PROJET_TASK_HPP

#include <sstream>

// Classe qui définie une tache
class Task {
public:
    // Indice de la tâche
    int i;
    // durée opératoire
    int p;
    // Date de début
    int r;
    // poid de la tâche
    int w;

    /**
     * Constructeur par defaut, initialise tout à 0
     */
    Task():i(0),p(0),r(0),w(0) {}
    /**
     * Constructeur de tache
     * @param p Durée opératoire
     * @param r Date de début au plus tôt
     * @param w poid (importance) de la tâche
     */
    Task(int i, int p, int r, int w):i(i),p(p),r(r),w(w) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << "task[i:"<<i<<",p:"<<p<<",r:"<<r<<",w:"<<w<<"]";
        return oss.str();
    }

    friend std::ostream& operator<<(std::ostream& flux, const Task& task) {
        return flux << task.toString();
    }
};

#endif