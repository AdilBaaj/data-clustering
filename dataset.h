#ifndef DEF_DATASET
#define DEF_DATASET

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <data.h>

//--------------------------------------------------------------------------
class Dataset // Conteneur de donnees de n entree et p colonnes, les colonnes sont des Datas definit avec la classe Data
{
    
public:
    
    Dataset(); // Constructeur par defaut, cree un dataset de 1 colonne et 1 ligne
    Dataset(std::string path, unsigned long rows, unsigned long columns); // Constructeur surcharge, cree un dataset a partir d'un fichier csv, indiquer si le fichier contient une ligne d'entete
    Dataset(int rows, int columns);
    Dataset Dataset2D(int x,int y); // Methode qui recupere les colonnes x et y pour creer un dataset de 2 colonnes
    Dataset Dataset3D(int x,int y,int z); // methode qui recupere les colonnnes x, y et z pour creer un dataset de 3 colonnes
    
    unsigned int get_nb_rows(); // renvoie le nombre de lignes
    unsigned int get_nb_columns(); // renvoie le nombre de colonnes
    double get_element(int i,int j); // renvoie l'element (i,j)
    void set_element(int i,int j,double value); // change la valeur de l'element (i,j)
    Data get_data(int j); // Recupere une colonne du dataset
    void set_data(int j, Data full_data); // change une colonne du dataset
    void set_header(int j, std::string header = false); // change le header d'une colonne
    
    ~Dataset(); // destructeur    
private:
    
    unsigned int m_columns; // nombre de colonnes
    unsigned int m_rows; // nombre de lignes
    std::vector<Data> m_dataset; // donnees
    std::vector<std::string> m_headers; // headers
    std::string m_path;
};


#endif
