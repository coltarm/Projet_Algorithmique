#ifndef DEF_NODE
#define DEF_NODE
#include <string>

class Node
{
    public :
        Node(std::string caract, int freq, Node* filsG, Node* filsD);
        int getFreq()const;
        std::string getCar()const;
        Node* Get_fils_droit() const;
        Node* Get_fils_gauche() const;
        bool operator<(const Node &noeuds)const ;
        bool operator==(const Node &noeuds) const;
        bool est_feuille();

    private:
        std::string label;
        int frequence;
        Node* fils_droit;
        Node* fils_gauche;


};
#endif
