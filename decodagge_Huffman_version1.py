
class Node:
    def __init__(self, label, frequence, fils_gauche=None, fils_droit=None ):
        self.frequence = frequence
        self.label = label
        self.fils_gauche = fils_gauche
        self.fils_droit = fils_droit

    def getfils_gauche(self):
        return self.fils_gauche

    def getfils_droit(self):
        return self.fils_droit
    
    def get_frequence(self):
        return self.frequence

    def  __le__(self, node):
        return self.frequence <= node.frequence

    def  __lt__(self, node):
        if self.frequence != node.frequence:
            return self.frequence < node.frequence
        
        elif self.label is None and node.label is None:
            return  self.tampon(self.getfils_droit(), node.getfils_droit()) #self.getfils_droit() < node.getfils_droit()
        elif self.label is None and node.label is not None:
            return False
        elif self.label is not None and node.label is None:
            return True
        
        else:
            return self.label < node.label
        
    def tampon(self,Node1,Node2):
        if Node1.label is not None and Node2.label is not None:
            return Node1.label < Node2.label
        elif Node1.label is None and Node2.label is not None:
            return False
        elif Node1.label is not None and Node2.label is None:
            return True
        else:
            return tampon(Node1.getfils_droit(), Node2.getfils_droit())



    def est_feuille(self):
        if self.getfils_droit() is None and self.getfils_gauche() is None:
            return True
        return False


def affiche(L):
    RESULTAT = []
    for i in L:
        RESULTAT.append(str( i.label) + " "+str(i.frequence))
    return RESULTAT
                        




#on va supposer que le message à décompressser est composé de plusieurs caractère, est que l'on a un dictionnaire de la forme:
# dict = {caractère : freq}
def transform(dict):
    L=[]
    for (k,v) in dict.items():
        L.append(Node(k, v, None, None))
    return L

def return_plus_petit_element_de_la_liste(L):
    #10111000110110111101010000000
    '''mini = min(L)
    L.remove(mini)
    return(mini)'''
    mini = L[0]
    L.remove(mini)
    return mini


def ajout_element(L,element):

    a=0
    for i in range(len(L)):
    
        if element < L[i]:
            L.insert(i, element)
            a=1
            break
    if a==0:
        L.append(element)




def determine_racine(L):
    #on parcours la liste et on choisit les 1 plus petit élément
    while len(L)>=2:
        print(affiche(L))
        n1 = return_plus_petit_element_de_la_liste(L)
        n2 = return_plus_petit_element_de_la_liste(L)

        n = Node(None, n1.frequence+n2.frequence, n1, n2)
        ajout_element(L,n)
    print(affiche(L))
    racine = L.pop()
    return racine

def code_huffman(noeuds):
    dict={}
    code=""
    code_huffman_sous_section(dict, noeuds, code)
    return dict


    

def code_huffman_sous_section(dict, noeuds, code):
    if noeuds.est_feuille():
        dict[noeuds] = code
    else:
        print(noeuds.label, "                  ", noeuds.frequence, "fils droit : ", noeuds.getfils_droit().label," ", noeuds.getfils_droit().frequence,"\n fils gauche : ", noeuds.getfils_gauche().label," ",noeuds.getfils_gauche().frequence, "\n")
        code_huffman_sous_section(dict, noeuds.getfils_droit(), code +'1')
        code_huffman_sous_section(dict, noeuds.getfils_gauche(), code + '0')


def determine_code_bin():
    f = open('D:\IDU\PROJ631-algorithmique\donnees\exemple_comp.bin', "rb")
    num = list(f.read())
    f.close()
    binaire = ""
    print(num)
    for k in num:
        bin_tamp = bin(k)
        n = len(bin_tamp)
        binaire += bin_tamp[2:n]
    return binaire

def nbre_moyen(code_bin):
    nbre_caract = nbre_caract()
    moyenne = len(code_bin)/nbre_caract
    return moyenne

    

def nbre_caract():
    with open(r"D:\IDU\PROJ631-algorithmique\donnees\exemple_freq.txt",'r') as file :
        content = file.readlines()
    file.close()
    somme=0
    for i in range(1,len(content)):
        a=content[i]
        somme += a[2:len(a)]
    return somme



def calcule_compression(code_binaire):
    #on parcours le fichier frequence et on calcule le volume du nombre de caractère par son volume 
    #et on mesure la longueur du code binaire et on le multiplie par le nombre de fois où on le retrouve dans le fichier binaire
    # open the file using open() function
    with open(r"D:\IDU\PROJ631-algorithmique\donnees\exemple_freq.txt",'r') as file :
        content = file.readlines()
    file.close()
    taille_chiffre = 0
    somme = 0
    for i in range(1,len(content)):
        taille_chiffre += len(bin(int(content[i][2:len(content[i])])))-2
        somme += int(content[i][2:len(content)])
    print(somme)
    volume_init = somme * 8
    nbre_lettre = int(content[0])
    volume_fin = len(code_binaire) + taille_chiffre + nbre_lettre *8
    gain = 1 - volume_fin/volume_init
    return gain



   




    
if __name__ == '__main__':

#prenons par exemple le dictionnaire suivant
    dictionnaire = { 'b': 1, 'j': 1, 'n': 1, 'r': 1, 'u': 1,'!': 2, 'o': 2 }
    #dictionnaire = { 'W' : 1 ,'a': 1, 'd': 1, 'e': 1, 'k': 1, 'p': 1, 'i': 3}
    code_binaire=""
    #il faudra ouvrir le fichier des fréquences et crée le fictionnaire
    #même chose pour le code binaire du fichier compresser

    
    print(bin(23))
    code_bin = determine_code_bin()
    print(code_bin)
    calcule_compression(code_bin)

    nouriture =[]
    '''
    L = transform(dictionnaire)
    print(L[len(L)-1].label)
    racine = determine_racine(L)
    dict_code = code_huffman(racine)
    for (k,v) in dict_code.items():
        print("lettre : ", k.label," code :", v,"\n")
    print(dict_code)
    resultat=""
    tampon=""
    for a in code_bin:
        tampon+=a
        nouriture.append(tampon)
        print(nouriture)
        #on cherche le code similaire à ce que l'on a et on le remplace par le caractère que l'on veut
        for (noeuds,code) in dict_code.items():
            if tampon == code:
                resultat+=noeuds.label
                nouriture.append(noeuds.label)
                tampon=""

    print(resultat)
    # on peut réécrire dans un fichier le résultat mais il faut faire le test avant.

'''



