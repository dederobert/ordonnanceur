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

// Définie le nombre de taĉhe à générer
#define NB_TACHE 10

// Définie le nombre d'individu et de génération pour l'algo génétique
#define NB_INDIVIDU 10
#define NB_GENERATION 10

using namespace std;

int main(int argc, char** argv) {
    //Permet de gérer les paramètre
    ParameterAnalyzer pa(argc, argv);
    int i = 0;

    if (pa.data["verbose"]) cout << endl << endl << "\033[1;4mTACHES\033[0m" << endl << endl;
    if (pa.data["verbose"]) cout << "Création de " << NB_TACHE << " tâches" << endl;
    // Créations de NB_TACHE taches
    std::vector<Task> tasks;
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
    // Affichage des tâches
    cout << "Tâche | rj | wj | pj" << endl;
    for (Task task:tasks) {
        cout << " " << i++ << "   | " << task.r << " | " << task.w << " | " << task.p << endl;
    }


    if (pa.data["heuristique"]) {
        if (pa.data["verbose"]) cout << endl << endl << "\033[1;4mHEURISTIQUE\033[0m" << endl << endl;
        // Création des machines et des heuristiques
        Machine m1PJ;
        Machine m2PJ;
        Machine m1RJ;
        Machine m2RJ;
        Machine m1WJ;
        Machine m2WJ;
        Machine m1PJWJ;
        Machine m2PJWJ;

        Heuristique *hPJ = new HeuristiqueTriePJ();
        Heuristique *hRJ = new HeuristiqueTrieRJ();
        Heuristique *hWJ = new HeuristiqueTrieWJ();
        Heuristique *hPJWJ = new HeuristiqueTriePJWJ();

        // calcul des heuristiques
        if (pa.data["pj"])
            hPJ->predict(m1PJ, m2PJ, tasks);
        delete hPJ;

        if (pa.data["wj"])
            hWJ->predict(m1WJ, m2WJ, tasks);
        delete hWJ;

        if (pa.data["rj"])
            hRJ->predict(m1RJ, m2RJ, tasks);
        delete hRJ;

        if (pa.data["pjwj"])
            hPJWJ->predict(m1PJWJ, m2PJWJ, tasks);
        delete hPJWJ;

        //Affichage des résultats
        if (pa.data["pj"]) {
            if (pa.data["verbose"]) cout << "\033[4;32m";
            cout << "Heuristique trie PJ";
            if (pa.data["verbose"]) cout << "\033[0;42;30m";
            cout << endl << "M1:" << m1PJ << endl;
            cout << "M2:" << m2PJ << "\033[0m"<< endl;
        }

        if (pa.data["wj"]) {
            if (pa.data["verbose"]) cout << "\033[4;32m";
            cout << "Heuristique trie WJ";
            if (pa.data["verbose"]) cout << "\033[0;42;30m";
            cout << endl << "M1:" << m1WJ << endl;
            cout << "M2:" << m2WJ << "\033[0m"<< endl;
        }

        if (pa.data["rj"]) {
            if (pa.data["verbose"]) cout << "\033[4;32m";
            cout << "Heuristique trie RJ";
            if (pa.data["verbose"]) cout << "\033[0;42;30m";
            cout << endl << "M1:" << m1RJ << endl;
            cout << "M2:" << m2RJ<< "\033[0m" << endl;
        }

        if (pa.data["pjwj"]) {
            if (pa.data["verbose"]) cout << "\033[4;32m";
            cout << "Heuristique trie PJWJ";
            if (pa.data["verbose"]) cout << "\033[0;42;30m";
            cout << endl << "M1:" << m1PJWJ << endl;
            cout << "M2:" << m2PJWJ << "\033[0m"<< endl;
        }
    }

    /*******************************************\
    *          ALGORITHME GENETIQE             *
    \*******************************************/
    if (pa.data["genetique"]) {
        if (pa.data["verbose"]) cout << endl << endl << "\033[1;4mGENETIQUE\033[0m" << endl << endl;

        // Création de l'algo génétique
        auto *g = new Genetique<int>();
        std::vector<int> indexes = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        auto cRes = g->run(NB_GENERATION, NB_INDIVIDU,tasks,indexes,pa.data["verbose"]);

        int resultatGenetique = evaluateChromosome<int>(&cRes, tasks);

        Machine m1,m2;
        Chromosome2Machine(m1,m2,&cRes,tasks);

        // AFFICHAGE DU RESULTAT
        if (pa.data["verbose"]) {
            cout << endl <<"\033[42;30m"<< endl << "Le meilleur résultat est " << resultatGenetique
                 << endl << "Obtenue avec " << NB_GENERATION
                 << " générations sur " << NB_INDIVIDU << " individus\033[0m" << endl
                 << "\033[0;4mPremière machine" << endl << "\033[0;32m" << m1 << endl
                 << "\033[0;4mDeuxième machine" << endl << "\033[0;32m" << m2 << "\033[0m" << endl;
        } else {
            cout << endl << "Resultat algo génétique " << resultatGenetique << endl
                 << "M1" << endl << m1 << endl << "M2" << endl << m2;
        }

            // Memory clear
        delete g;
    }
    return EXIT_SUCCESS;
}