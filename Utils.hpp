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
        data["genetique"] = argc == 1;
        data["heuristique"] = argc == 1;

        data["pj"] = argc == 1;
        data["rj"] = argc == 1;
        data["wj"] = argc == 1;
        data["pjwj"] = argc == 1;

        bool precIsHeur = false;


        for (int i = 1; i < argc; ++i){
            std::string cmd(argv[i]);
            if (cmd == "--verbose" || cmd == "-v") {
            	precIsHeur = false;
                data["verbose"] = true;
            }
            else if (cmd == "--genetique" || cmd == "-g"){
            	precIsHeur = false;
                data["genetique"] = true;
            }
            else if (cmd == "--heuristique" || cmd == "-h"){
            	precIsHeur = true;
                data["heuristique"] = true;
            }
            else if (cmd == "rj" && precIsHeur){
                data["rj"] = true;
            }
            else if (cmd == "wj" && precIsHeur){
                data["wj"] = true;
            }
            else if (cmd == "pj" && precIsHeur){
                data["pj"] = true;
            }
            else if (cmd == "pjwj" && precIsHeur){
                data["pjwj"] = true;
            }
            else if (cmd == "all" && precIsHeur){
            	data["rj"] = true;
                data["wj"] = true;
                data["pj"] = true;
                data["pjwj"] = true;
            }
            else if (cmd == "-gh" || cmd == "-hg") {
            	precIsHeur = true;
                data["heuristique"] = true;
                data["genetique"] = true;
            }
            else if(i != 0) {
                fprintf(stderr, "Usage: %s [OPTIONS]\nOPTIONS:\n\t--verbose|-v Mode verbeux\n"
                        "\t--genetique|-g Utiliser algo genetique"
                        "\n\t--heuristique=HEURISTIQUE|-h Utiliser la ou les heuristique(s) (pj, rj, wj, pjwj, all)\n",argv[0]);
                exit(EXIT_FAILURE);
            }
        }

    }

    std::map<std::string, bool> data;

};

#endif //PROJET_UTILS_HPP
