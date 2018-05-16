#include <iostream>
#include <random>

#include "struct/task.hpp"
#include "struct/Machine.hpp"
#include "heuristique/Heuristique.hpp"
#include "heuristique/HeuristiqueTriePJWJ.hpp"
#include "heuristique/HeuristiqueTrieRJ.hpp"
#include "heuristique/HeuristiqueTrieWJ.hpp"
#include "heuristique/HeuristiqueTriePJ.hpp"
#include "genetique/Genetique.hpp"

#define NB_TACHE 10
#define NB_INDIVIDU 10
std::vector<Task> tasks;

using namespace std;
int main() {
    // Création des machines et de l'heuristique
    Machine m1PJ;
    Machine m2PJ;
    Machine m1RJ;
    Machine m2RJ;
    Machine m1WJ;
    Machine m2WJ;
    Machine m1PJWJ;
    Machine m2PJWJ;

    Heuristique* hPJ;
    Heuristique* hRJ;
    Heuristique* hWJ;
    Heuristique* hPJWJ;

   std::vector<Chromosome<int>> generation1;
   std::vector<Chromosome<int>*> generation2;
    Genetique<int>* g = new Genetique<int>();

    // Choix de l'heuristique (A CHANGER)
    hPJ = new HeuristiqueTriePJ();
    hRJ = new HeuristiqueTrieRJ();
    hWJ = new HeuristiqueTrieWJ();
    hPJWJ = new HeuristiqueTriePJWJ();

    // Créations de NB_TACHE taches

    {
        tasks.emplace_back(0,3,3,2);
        tasks.emplace_back(1,2,6,10);
        tasks.emplace_back(2,1,0,1);
        tasks.emplace_back(3,9,10,2);
        tasks.emplace_back(4,1,18,5);
        tasks.emplace_back(5,17,5,4);
        tasks.emplace_back(6,6,2,1);
        tasks.emplace_back(7,10,3,6);
        tasks.emplace_back(8,5,8,8);
    }

    cout << endl << endl << "ALGORITHME GENETIQUE" << endl << endl;
    // Création des individu
    std::vector<int>indexes = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    std::random_device rd;
    std::mt19937 shuffler(rd());
    Machine mg1;
    Machine mg2;

    cout << "Generation des individue" << endl;
    for (int i =0;i< NB_INDIVIDU;i++){
        std::shuffle(indexes.begin(), indexes.end(), shuffler);
        generation1.emplace_back(indexes);
    }

    int z=0;
    cout << "Generation 1" << endl;
    for(const auto &c:generation1) {
        cout << "Individu " <<z++ << endl;
        cout << "Somme Cj Wj :" << evaluateChromosome<int>(c, tasks) << endl;
    }

    std::shuffle(generation1.begin(), generation1.end(), shuffler);
    for(int i = 0; i < generation1.size()-1; i+=2) {
        generation2.push_back(g->cross(generation1[i], generation1[i+1]));
        generation2.push_back(g->mutation(generation1[i]));
        generation2.push_back(g->mutation(generation1[i+1]));

    }

    cout << endl << "Generation 2" << endl;
    std::sort(generation2.begin(), generation2.end(), [](Chromosome<int>* a, Chromosome<int>* b) {
        return evaluateChromosome<int>(*a, tasks) > evaluateChromosome<int>(*b, tasks);
    });

    z=0;
    for(auto c:generation2) {
        cout << "Individu " <<z++ << endl;
        cout << "Somme Cj Wj :" << evaluateChromosome(*c, tasks) << endl;
    }

/*
    putTaskOnMachine(mg1, mg2, g->Chromosome2Tasks(generation1.back(), tasks));
    // On test si il y a un wait sur m1 et on décalle
    if (mg1.isWaiting())
        mg1.shiftTask(mg1.sumWaitingTime());

    // On test si il y a un wait sur m2 et on décalle
    if (mg2.isWaiting())
        mg2.shiftTask(mg2.sumWaitingTime());
    cout << mg1 << endl;
    cout << mg2 << endl;
    mg1.clear();
    mg2.clear();*/


    return 0;

    cout << "Resultat croisement: " << endl;
    cout << mg1 << endl;
    cout << mg2 << endl;


    // Affichage des tâches
    cout << "Tâche | rj | wj | pj" << endl;
    int i = 0;
    for (Task task:tasks) {
        cout << " "<<i++<<"   | " << task.r << " | " << task.w << " | " << task.p << endl;
    }

    // calcul des heuristiques
    hPJ->predict(m1PJ, m2PJ, tasks);
    delete hPJ;

    hWJ->predict(m1WJ, m2WJ, tasks);
    delete hWJ;

    hRJ->predict(m1RJ, m2RJ, tasks);
    delete hRJ;

    hPJWJ->predict(m1PJWJ, m2PJWJ, tasks);
    delete hPJWJ;

    //Affichage des machines
    cout << "Heuristique trie PJ" << endl;
    cout << "M1:" << m1PJ << endl;
    cout << "M2:" << m2PJ << endl;

    cout << "Heuristique trie WJ" << endl;
    cout << "M1:" << m1WJ << endl;
    cout << "M2:" << m2WJ << endl;

    cout << "Heuristique trie RJ" << endl;
    cout << "M1:" << m1RJ << endl;
    cout << "M2:" << m2RJ << endl;

    cout << "Heuristique trie PJWJ" << endl;
    cout << "M1:" << m1PJWJ << endl;
    cout << "M2:" << m2PJWJ << endl;

}