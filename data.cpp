#include "data.h"
#include <iostream>
#include <string>

/* 
- cr�e un header automatiquement si pas de header
*/

//----------------------------------------------------------------------
// CONSTRUCTEUR
Data::Data()
{
}

Data::Data(int rows, std::string header) : m_rows(rows), m_header(header)
{
    m_data.resize(m_rows);
}

//----------------------------------------------------------------------
// ACCESSEURS


unsigned int Data::get_nb_rows() // Renvoie le nombre de lignes
{
    return m_rows;
}

std::string Data::get_header()
{
    return m_header;
}

double Data::get_value(int i) // Renvoie la valeur i du data set
{
    return m_data[i];
}


void Data::set_value(int i,double value)
{
    m_data[i] = value;
}

void Data::set_header(std::string header)
{
    m_header = header;
}


//----------------------------------------------------------------------
// Destructeur




Data::~Data()
{
    m_rows = 0;
    m_data.clear();
}


