#include <iostream>

#include "struct/task.hpp"
#include "struct/Machine.hpp"
#include "heuristique/Heuristique.hpp"
#include "heuristique/HeuristiqueNaif.hpp"
#include "heuristique/HeuristiqueTriePJWJ.hpp"

#define NB_TACHE 10

using namespace std;
int main() {
    // Création des machines et de l'heuristique
    Machine m1;
    Machine m2;
    Heuristique* h;

    // Choix de l'heuristique (A CHANGER)
    h = new HeuristiqueTriePJWJ();

    // Créations de NB_TACHE taches
    std::vector<Task> tasks;
    {
        tasks.emplace_back(1,3,3,2);
        tasks.emplace_back(2,2,6,10);
        tasks.emplace_back(3,1,0,1);
        tasks.emplace_back(4,9,10,2);
        tasks.emplace_back(5,1,18,5);
        tasks.emplace_back(6,17,5,4);
        tasks.emplace_back(7,6,2,1);
        tasks.emplace_back(8,10,3,6);
        tasks.emplace_back(9,5,8,8);
    }

    // Affichage des tâches
    cout << "Tâche | rj | wj | pj" << endl;
    int i = 0;
    for (Task task:tasks) {
        cout << " "<<i++<<"   | " << task.r << " | " << task.w << " | " << task.p << endl;
    }

    // calcul de l'heuristique
    h->predict(m1, m2, tasks);
    delete h;

    //Affichage des machines
    cout << "M1:" << m1 << endl;
    cout << "M2:" << m2 << endl;
}