#ifndef DEF_DATA
#define DEF_DATA

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

class Data
{
public:
    Data();
    Data(int rows, std::string header);//Constructeur
    double get_value(int i);
    void set_value(int i,double value);
    unsigned int get_nb_rows();
    std::string get_header();
    void set_header(std::string header);
    ~Data();
    
private:
    
    int m_rows;
    std::vector<double> m_data;
    std::string m_header;
};


#endif
