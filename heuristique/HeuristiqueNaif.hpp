#include "Heuristique.hpp"

//Heuristique qui place les tâches succesivement sur m1 et m2
class HeuristiqueNaif: public Heuristique{

    void predict(Machine& m1, Machine& m2, const std::vector<Task>& tasks) const override {
        for(int i = 0; i < tasks.size(); i++) {
            // si l'indice est paire on place la tâche sur m1 sinon sur m2
            if (i%2)
                m1 = m1 + tasks[i];
            else
                m2 = m2 + tasks[i];
        }
    }

};