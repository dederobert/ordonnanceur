//
// Created by dede on 16/05/18.
//

#ifndef PROJET_CHROMOSOME_HPP
#define PROJET_CHROMOSOME_HPP

#include <vector>
template<typename T>
class Chromosome {
    std::vector<T> tab;
public:
    explicit Chromosome(std::vector<T> tab):tab(tab){}
    Chromosome() = default;
    Chromosome(const Chromosome& c) {
        for (int i = 0; i < c.size();i++)
            tab.push_back(c[i]);

    }

    Chromosome& operator+(T element) {
        tab.push_back(element);
        return *this;
    }

    void set(int index, T element) {
        tab[index] = element;
    }

    T operator[] (int index) const {
        return tab[index];
    }

    unsigned long size() const {
        return tab.size();
    }

    void permute(int i, int i1) {
        int t = tab[i];
        tab[i] = tab[i1];
        tab[i1] = t;
    }
    friend std::ostream& operator<<(std::ostream& flux, const Chromosome& c) {
        for (int i = 0; i < c.size(); i++)
            flux << c[i] << ",";
        return flux;
    }
};
#endif //PROJET_CHROMOSOME_HPP
