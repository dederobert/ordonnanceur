//
// Created by dede on 16/05/18.
//

#ifndef PROJET_GENETIQUEORDRETACHE_HPP
#define PROJET_GENETIQUEORDRETACHE_HPP

#include <cstdlib>
#include <ctime>
#include <Utils.hpp>


template<typename T>
std::vector<Task> Chromosome2Tasks(const Chromosome<T> &c, const std::vector<Task> &tasks) {
    std::vector<Task> res;
    for (int i = 0; i < c.size(); i++)
        res.push_back(tasks[c[i]]);
    return res;
}

template<typename T>
void Chromosome2Machine(Machine& m1, Machine& m2, const Chromosome<T>* c, const std::vector<Task>& tasks) {
    putTaskOnMachine(m1, m2, Chromosome2Tasks(*c, tasks));
    // On test si il y a un wait sur m1 et on décalle
    if (m1.isWaiting())
        m1.shiftTask(m1.sumWaitingTime());

    // On test si il y a un wait sur m2 et on décalle
    if (m2.isWaiting())
        m2.shiftTask(m2.sumWaitingTime());
}

template<typename T>
int evaluateChromosome(const Chromosome<T>* c,const std::vector<Task>& tasks){
    Machine mg1, mg2;
    Chromosome2Machine(mg1, mg2, c, tasks);

    if (mg1.sumCjWj > mg2.sumCjWj)
        return mg1.sumCjWj;
    return mg2.sumCjWj;
}

template<typename T>
class Genetique {
public:
    Chromosome<T> *cross(Chromosome<T>* c1, Chromosome<T>* c2) const {
        Chromosome<T> *c = new Chromosome<int>();
        bool found = false;
        int i, j = 0;
        for (i = 0; i < c1->size() / 2; i++)
            *c = *c + (*c1)[i];

        for (; i < c1->size();) {
            for (int k = 0; k < i; k++)
                if ((*c2)[j] == (*c)[k]) {
                    j++;
                    found = true;
                    break;
                }
            if (!found) {
                *c = *c + (*c2)[j++];
                i++;
            }
            found = false;
        }
        return c;
    }

    Chromosome<T> *mutation(Chromosome<T>* c) const {
        auto *cp = new Chromosome<T>(*c);
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        int random1, random2;

        do {
            random1 = std::rand();
            random2 = std::rand();
            random1 = static_cast<int>(random1 / static_cast<double>(RAND_MAX) * c->size());
            random2 = static_cast<int>(random2 / static_cast<double>(RAND_MAX) * c->size());
        } while (random1 == random2);

        cp->permute(random1, random2);
        return cp;
    }

    Chromosome<T> run(int nbGeneration, int nbIndividu,const std::vector<Task>& tasks, std::vector<T> elements,bool verbose) {
        Chromosome<T> bestChromosome;
        int bestRes = std::numeric_limits<int>::max();;

        int i;
        std::random_device rd;
        std::mt19937 shuffler(rd());

        //Création des générations pour l'algo génétique
        std::vector<Chromosome<T> *> generation1;
        std::vector<Chromosome<T> *> generationNext;

        // Création des individu
        // Pour chaque individu, on place les tâches dans un ordre aléatoire
        if (verbose) std::cout << "Generation des individu";
        for (i = 0; i < nbIndividu; i++) {
            std::shuffle(elements.begin(), elements.end(), shuffler);
            generation1.push_back(new Chromosome<T>(elements));
        }


        for (i = 0; i < nbGeneration; i++) {
            //On garde le meilleur des résultats
            int eval = evaluateChromosome(generation1[0], tasks);
            if (eval < bestRes) {
                bestRes = eval;
                bestChromosome = *generation1[0];
            }

            std::shuffle(generation1.begin(), generation1.end(), shuffler);
            for (int j = 0; j < generation1.size() - 1; j += 2) {
                generationNext.push_back(cross(generation1[j], generation1[j + 1]));
                generationNext.push_back(mutation(generation1[j]));
                generationNext.push_back(mutation(generation1[j + 1]));
                delete generation1[j];
                delete generation1[j + 1];
            }
            // On trie les individus selont leurs évaluation
            std::sort(generationNext.begin(), generationNext.end(), [tasks](Chromosome<T> *a, Chromosome<T> *b) {
                return evaluateChromosome<T>(a, tasks) <= evaluateChromosome<T>(b, tasks);
            });

            generation1.clear();
            for (int j = 0; j < nbIndividu; j++) {
                generation1.push_back(generationNext[j]);
            }
            generationNext.clear();

            if (verbose){
                int z = 0;
                std::cout << std::endl << std::endl << "Generation " << i << std::endl;
                for (auto &j : generation1) {
                    std::cout << "Somme Cj Wj :" << evaluateChromosome<T>(j, tasks) << std::endl;
                }
            }
        }
        return bestChromosome;

    }
};


#endif //PROJET_GENETIQUEORDRETACHE_HPP
