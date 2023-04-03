#include "Node.hpp"

using namespace std;



Node::Node(std::string caract, int freq, Node *filsG, Node *filsD)
{
    label = caract;
    frequence = freq;
    fils_droit = filsD;
    fils_gauche = filsG;

}



int Node::getFreq()  const
{
    return this->frequence;
}
string Node::getCar() const{
    return this->title;
}

Node* Node::Get_fils_gauche()const{
    return this->fils_gauche;
        
}
Node* Node::Get_fils_droit() const{
    return this->fils_droit;
}

bool Node::est_feuille(){
    if ((this->fils_droit==nullptr) and (this->fils_gauche==nullptr)){
        return true;
    }
    else{
        return false;

    }
}


bool Node::operator<(const Node &noeuds) const{
    return this->frequence <noeuds.getFreq();
}
bool Node::operator==(const Node &noeuds) const{
    return this == noeuds;
}
