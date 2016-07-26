#include "dataset.h"
#include "math.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>


namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

using namespace std;

//========================================================================================================
// CLASSE DATASET

//----------------------------------------------------------------------
// CONSTRUCTEUR
Dataset::Dataset():m_rows(1),m_columns(1) // Constructeur par dŽfaut pour le dataset (1 colonne, 1 ligne)
{
    m_dataset.resize(m_columns);
    m_headers.resize(m_columns);

    for (int j = 0; j < m_columns; ++j) // pour chaque colonne
    {
        m_dataset[j] = Data(m_rows, patch::to_string(j)); //chaque colonne est une data avec pour nom son numŽro
        m_headers[j] = m_dataset[j].get_header(); // chaque nom de colonne est le nom de la data correspondant
    }
}


Dataset::Dataset(int rows,int columns):m_rows(rows),m_columns(columns) // Constructeur surchargŽ de plusieurs lignes et plusieurs colonnes
{
    m_dataset.resize(m_columns);
    m_headers.resize(m_columns);

    for (int j = 0; j < columns; ++j) // Pour chaque colonne
    {
        m_dataset[j] = Data(m_rows,patch::to_string(j)); // On crŽe une Data
        m_headers[j] = m_dataset[j].get_header(); // On affecte bien le nom correspondant
    }
}

Dataset::Dataset(std::string path, unsigned long rows, unsigned long columns): m_rows(rows), m_columns(columns), m_path(path)
    // Surcharge du constructeur, crŽe un dataset ˆ partir d'un fichier csv (ˆ partir du chemin du fichier)
    // Il doit tre indiquŽ si le fichier comporte les noms des datas ou non
{
    m_dataset.resize(m_columns); // crŽe un Dataset de n datas
    m_headers.resize(m_columns); // crŽe un vecteur de n noms

    for (int j = 0; j < m_columns; ++j) // pour chaque colonne
    {
        m_dataset[j] = Data(m_rows,patch::to_string(j)); // on crŽe une data avec pour nom le numŽro de la colonne
        m_headers[j] = m_dataset[j].get_header(); // on change le nom avec le nom de la data correspondant
    }

    ifstream  data(path.c_str()); // on rŽcupre le flux en lecture ˆ partir du chemin du fichier
    string line; // on crŽe une string qui stockera une ligne l'une aprŽs l'autre
    int row = 0; // variable d'itŽration sur les lignes
    int col = 0; // variable d'itŽrations sur les colonnes

    while(getline(data,line))
    {
        stringstream  lineStream(line);
        string        cell;
        while(getline(lineStream,cell,','))
        {
            if( 0 <= int(cell.find("\r"))) //si retour ˆ la ligne
            {
                std::string a;
                std::string b;

                for(int i = 0; i < int(cell.find("\r")); i++)
                {
                    a += cell[i];
                }

                for(int i = int(cell.find("\r")) + 1; i < cell.size(); i++)
                {
                    b += cell[i];
                }

                m_dataset[col].set_value(row, std::atof(a.c_str()));
                row++;
                col = 1;
                m_dataset[0].set_value(row, std::atof(b.c_str()));
            }
            else
            {
                m_dataset[col].set_value(row, std::atof(cell.c_str())); // on stocke la valeur dans le dataset
                col++; // on itre sur les colonnes
            }
        }
    }
}


Dataset Dataset::Dataset2D(int x,int y) // Création d'un dataset à deux colonnes à partir d'un dataset en choisissant les deux colonnes qui nous intéressent
{
    Dataset data2D(m_rows,2);
    data2D.set_data(0,m_dataset[x]);
    data2D.set_data(1,m_dataset[y]);
    return data2D;
}

Dataset Dataset::Dataset3D(int x,int y,int z) // Idem qu'au dessus mais pour 3 colonnes
{
    Dataset data3D(m_rows,3);
    data3D.set_data(0,m_dataset[x]);
    data3D.set_data(1,m_dataset[y]);
    data3D.set_data(2,m_dataset[z]);
    return data3D;
}


//----------------------------------------------------------------------
// LECTURE DEPUIS CSV




void read_csv(string path)
{
    ifstream  data(path.c_str());
    string line;
    while(getline(data,line))
    {
        stringstream  lineStream(line);
        string        cell;
        while(getline(lineStream,cell,','))
        {
            cout << cell << endl;
            getchar();
        }
    }
}


//----------------------------------------------------------------------
// DESTRUCTEUR

Dataset::~Dataset()
{
    m_rows = 0;
    m_columns = 0;
    m_headers.clear();
    m_dataset.clear();
}

//----------------------------------------------------------------------
// ACCESSEURS

unsigned int Dataset::get_nb_rows() // Renvoie le nombre de lignes
{
    return m_rows;
}

unsigned int Dataset::get_nb_columns() // Renvoie le nombre de colonnes
{
    return m_columns;
}


double Dataset::get_element(int i,int j) // renvoie la valeur (i,j) du dataset
{
    return m_dataset[j].get_value(i);
}

void Dataset::set_element(int i,int j,double value) // affecte une valeur à l'élément (i,j)
{
    m_dataset[j].set_value(i,value);
}

void Dataset::set_header(int j, string header) // change le header j du dataset
{
    m_headers[j] = header;
}

Data Dataset::get_data(int j) // récupère la colonne j du dataset
{
    return m_dataset[j];
}

void Dataset::set_data(int j,Data full_data) // change complètement la colonne j d'un dataset à partir d'une data
{
    m_dataset[j] = full_data;
}




