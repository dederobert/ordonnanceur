//
// Created by dede on 16/05/18.
//

#ifndef PROJET_UTILS_HPP
#define PROJET_UTILS_HPP

#include <string>
#include <map>
#include "struct/Machine.hpp"
#include "genetique/Chromosome.hpp"

template<typename T>
T max(T v1, T v2) {
    if (v1 > v2)
        return v1;
    return v2;
}


void putTaskOnMachine(Machine& m1, Machine& m2,const std::vector<Task>& tasks) {
    // On place toutes les tâches
    for (Task task : tasks) {
        // On test la machine la moins chargé
        // A voir si on test sur end ou sumCjWJ
        if (m1.end <= m2.end)
            m1 = m1 + task;
        else
            m2 = m2 + task;
    }
}

class ParameterAnalyzer {

public:
    ParameterAnalyzer(int argc, char** argv){
        data["verbose"] = false;
        data["genetique"] = false;
        data["heuristique"] = false;

        for (int i = 0; i < argc; ++i){
            std::string cmd(argv[i]);
            if (cmd == "--verbose" || cmd == "-v")
                data["verbose"] = true;
            else if (cmd == "--genetique" || cmd == "-g")
                data["genetique"] = true;
            else if (cmd == "--heuristique" || cmd == "-h")
                data["heuristique"] = true;
            else if(i != 0) {
                fprintf(stderr, "Usage: cmd [OPTIONS]\nOPTIONS:\n\t--verbose|-v Mode verbeux\n"
                        "\t--genetique|-g Utiliser algo genetique\n\t--heuristique|-h Utiliser heuristique\n");
                exit(EXIT_FAILURE);
            }
        }

    }

    std::map<std::string, bool> data;

};

#endif //PROJET_UTILS_HPP
