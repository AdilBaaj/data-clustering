#ifndef DEF_DATASET
#define DEF_DATASET

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <data.h>

//--------------------------------------------------------------------------
class Dataset // Model a set of data, each data corresponds to a column and is modeled itsefl by class Data
{
    
public:
    // Default Constructor, create a dataset with one column and one row
    Dataset(); 

    // Overloaded constructor, create dataset with "rows" rows and "columns" columns with header
    //TO DO: change variable names
    Dataset(std::string path, unsigned long rows, unsigned long columns);
    Dataset(int rows, int columns);

    // Method that gets columns x and y and create a 2D sub-dataset out of it
    Dataset Dataset2D(int x,int y);

    // Method that gets columns x, y and z and create a 3-D sub-dataset out of it
    Dataset Dataset3D(int x,int y,int z); 
    
    //TO DO: finish doc
    unsigned int get_nb_rows(); 
    unsigned int get_nb_columns(); 
    double get_element(int i,int j);
    void set_element(int i,int j,double value);
    Data get_data(int j);
    void set_data(int j, Data full_data);
    void set_header(int j, std::string header = false);
    
    //Destructor
    ~Dataset();    
private:
    
    unsigned int m_columns; 
    unsigned int m_rows;
    std::vector<Data> m_dataset;
    std::vector<std::string> m_headers;
    std::string m_path;
};


#endif
