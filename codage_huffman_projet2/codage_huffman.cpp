#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "Node.hpp"
using namespace std;


bool compare_letter(pair<string, int> a,pair<string, int> b){
    return a.second < b.second; 
   /* if (a.second == b.second){
        return a.first<b.first;
        //return a.first.compare(b.first) < 0;
    }
    else{
        return a.second < b.second;
    }*/

}


void enleve_element(vector<Node>& vec, Node element){

    for ( int i = 0 ; i < vec.size() ; i++ )
{
   if ( vec[i] == element )
   {
       vec.erase(vec.begin()+i);
       
       break;
   }
}
}



Node construct_arbre(vector<Node>* Liste_feuille ){
    while(Liste_feuille->size()>1){
        Node* Node1 = &(*min_element(Liste_feuille->begin(), Liste_feuille->end())); //plus petit element de liste des noeuds
        enleve_element(*Liste_feuille, *Node1);
        Node* Node2= &(*min_element(Liste_feuille->begin(), Liste_feuille->end()));//second plus petit élément de la liste des noeuds
        enleve_element(*Liste_feuille, *Node2);
        Node Node3("", Node1->getFreq()+Node2->getFreq(), Node1, Node2);
        Liste_feuille->push_back(Node3);
    }
    Node racine = (*Liste_feuille)[0];
    return racine;
    //construction arbre
}




void Parcours_en_profondeur(Node* noeuds , string chaine, map<string,string>& dict_codes){
    if (noeuds->est_feuille()){
        dict_codes[noeuds->getCar()]=chaine;

    }
    else{
        Parcours_en_profondeur(noeuds->Get_fils_droit(), chaine+"1",dict_codes );
        Parcours_en_profondeur(noeuds->Get_fils_gauche() , chaine +"0",dict_codes);
    }
}

map<string,string> code_bin(Node racine){
    map<string,string> dict_codes;
    Parcours_en_profondeur(&racine, "",dict_codes);
    return dict_codes;
}

float deter_gain(int taille_code_fin, int taille_text_origine){
    float gain;
    gain = 1 -(taille_code_fin/(taille_text_origine*8));
    return gain;

}

float taille_moyenne(int taille_bin, int taille_text_origine){
    float moy = taille_bin/taille_text_origine;
    return moy;
}

string lecture_file(){
    
    ifstream file("D:/IDU/PROJ631-algorithmique/texte.txt");

    if (file){
        string line;
        string content;

        while(getline(file,line)){
            cout<< line<<endl;
            content += line;
        }
        cout<<content<<endl;
        return content;
    }
    else{
        cerr<<"impossible ouvrir fichier"<<endl;
    }
    return "";
}

bool is_in(string* caract, map<string,int>& dict){
    if (dict.count(*caract)){
        return true;
    }
    else{
        return false;
    }
}



map<string,int> compt_caracts(string* content){
    map<string , int> dict;
    //parcourir le fichier et ajouter au dictionnaire la lettre et le nombre de fois où on la rencontrait
    for(int i=0; i< (content->size()); i++){
        if (is_in((*content)[i], dict)){
            dict[string(1,(*content)[i])]++;
        }
        else{
            dict.insert(make_pair<string, int>((string(1,*content)[i]),1));
        }
    }
    return dict;
}

void printMap(vector<pair<string, int>> m){
    cout<<"[";
    for(auto &item : m){
        cout << item.first<<":"<<item.second<<" ";
    }
    cout<<"]\n";
}

vector<Node> liste_feuille(map<string , int>& dict){
    vector<pair<string, int>> vec(dict.begin(), dict.end());
    sort(vec.begin(), vec.end(), compare_letter);
    printMap(vec);
    dict.clear();
    vector<Node> Liste_noeuds;
    for(auto &it: vec){
        Node ajout_element(it.first,it.second, nullptr,nullptr);
        Liste_noeuds.push_back(ajout_element);
    }
    return Liste_noeuds;
}

string creation_code_fin(string* content,map<string,string> dict_code){
    string code_fin = "";
    for(int i=0; i<content->size();i++){
        for (auto &it : dict_code){
            if (content[i]==it.first){
                code_fin = code_fin + it.second;
            }
        }

    }
    return code_fin;

}



int main(){
    string content = lecture_file();
    map<string, int> dict= compt_caracts(&content);
    vector<Node> liste_noeuds = liste_feuille(dict);
    Node racine =construct_arbre(&liste_noeuds);
    map<string,string> dict_code = code_bin(racine);
    string code_fin = creation_code_fin(&content, dict_code);
    float gain = deter_gain(code_fin.size(),content.size());
    float moyenne = taille_moyenne(code_fin.size(),content.size());
    cout<<"le gain de la compression est de"<< gain<<endl;
    cout<<"la taille moyenne d'un caractère est de "<<moyenne<< " bits"<<endl;
    cout<<"code_finale"<< code_fin<<endl;

    // pour le moment on va supposer que la fonction de trie fonctionne
    // idée trier un dictionnaire semble impossive va rester trier par clé et refuse de bouger
    // on va donc créer une classe des feuille dans qui va contenir la lettre, la frequence, le fils gauche et le fils droit.
    // là j'en ai marre on va faire ça plus tard!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 


    return 0;
}
