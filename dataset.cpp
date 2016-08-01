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
// CLASS DATASET

//----------------------------------------------------------------------
// Constructor
Dataset::Dataset():m_rows(1),m_columns(1) // Default constructor for dataset (1 col, 1 row)
{
    m_dataset.resize(m_columns);
    m_headers.resize(m_columns);

    for (int j = 0; j < m_columns; ++j) // for each col
    {
        m_dataset[j] = Data(m_rows, patch::to_string(j)); //Each column is a data with its number as id
        m_headers[j] = m_dataset[j].get_header(); // Name of each column is the name of the corresponding data
    }
}


Dataset::Dataset(int rows,int columns):m_rows(rows),m_columns(columns)
{
    m_dataset.resize(m_columns);
    m_headers.resize(m_columns);

    for (int j = 0; j < columns; ++j) // for each column
    {
        m_dataset[j] = Data(m_rows,patch::to_string(j)); // We create a data
        m_headers[j] = m_dataset[j].get_header(); // Affect correponding name
    }
}

Dataset::Dataset(std::string path, unsigned long rows, unsigned long columns): m_rows(rows), m_columns(columns), m_path(path)
    // Create dataset from csv file (input is path of file)
    // Must precise if file contains headers for each column or not
{
    m_dataset.resize(m_columns); // Create dataset with n data
    m_headers.resize(m_columns); // create vector with n names

    for (int j = 0; j < m_columns; ++j) // loop on columns
    {
        m_dataset[j] = Data(m_rows,patch::to_string(j)); // create data with number of column as id
        m_headers[j] = m_dataset[j].get_header(); // give corresponding name
    }

    ifstream  data(path.c_str()); // read file from path
    string line;
    int row = 0;
    int col = 0;

    while(getline(data,line))
    {
        stringstream  lineStream(line);
        string        cell;
        while(getline(lineStream,cell,','))
        {
            if( 0 <= int(cell.find("\r"))) //If end of row
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
                m_dataset[col].set_value(row, std::atof(cell.c_str())); // keep value on dataset
                col++; // iterate on columns
            }
        }
    }
}


Dataset Dataset::Dataset2D(int x,int y) // Create a two columns sub-dataset from another dataset
{
    Dataset data2D(m_rows,2);
    data2D.set_data(0,m_dataset[x]);
    data2D.set_data(1,m_dataset[y]);
    return data2D;
}

Dataset Dataset::Dataset3D(int x,int y,int z) // Idem with three columns
{
    Dataset data3D(m_rows,3);
    data3D.set_data(0,m_dataset[x]);
    data3D.set_data(1,m_dataset[y]);
    data3D.set_data(2,m_dataset[z]);
    return data3D;
}


//----------------------------------------------------------------------
// Read from csv file

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
// Destructor

Dataset::~Dataset()
{
    m_rows = 0;
    m_columns = 0;
    m_headers.clear();
    m_dataset.clear();
}

//----------------------------------------------------------------------
// Getters

unsigned int Dataset::get_nb_rows() // Get number of rows
{
    return m_rows;
}

unsigned int Dataset::get_nb_columns() // Get number of columns
{
    return m_columns;
}


double Dataset::get_element(int i,int j) // Get value at position (i,j) of dataset
{
    return m_dataset[j].get_value(i);
}

void Dataset::set_element(int i,int j,double value) // Set value at (i,j) position
{
    m_dataset[j].set_value(i,value);
}

void Dataset::set_header(int j, string header) // Change header of j-th column
{
    m_headers[j] = header;
}

Data Dataset::get_data(int j) // get j-th column
{
    return m_dataset[j];
}

void Dataset::set_data(int j,Data full_data) // replace j-th column of dataset by a data
{
    m_dataset[j] = full_data;
}




