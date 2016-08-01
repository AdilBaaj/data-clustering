#include "data.h"
#include <iostream>
#include <string>

//----------------------------------------------------------------------
// Constructor
Data::Data()
{
}

Data::Data(int rows, std::string header) : m_rows(rows), m_header(header)
{
    m_data.resize(m_rows);
}

//----------------------------------------------------------------------
// Getters


unsigned int Data::get_nb_rows() // Get number of lines
{
    return m_rows;
}

std::string Data::get_header()
{
    return m_header;
}

double Data::get_value(int i) // Get the i-th value of dataset
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
// Destructor




Data::~Data()
{
    m_rows = 0;
    m_data.clear();
}


