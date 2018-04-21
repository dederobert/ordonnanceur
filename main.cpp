#include <iostream>

#include "struct/task.hpp"
#include "struct/Machine.hpp"
#include "heuristique/Heuristique.hpp"
#include "heuristique/HeuristiqueNaif.hpp"

#define NB_TACHE 10

using namespace std;
int main() {
    // Création des machines et de l'heuristique
    Machine m1;
    Machine m2;
    Heuristique* h;

    // Choix de l'heuristique (A CHANGER)
    h = new HeuristiqueNaif();

    // Créations de NB_TACHE taches
    std::vector<Task> tasks;
    for (int i = 0; i < NB_TACHE; ++i) {
        tasks.emplace_back(i,i,i);
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