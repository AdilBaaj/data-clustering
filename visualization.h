#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <dlib/matrix.h>
#include <vector>
#include <Eigen/Dense>


class visualization
{
public:

    visualization();
    visualization(int nbDim, int nbClus, std::vector< dlib::matrix<float> > input_data, std::vector<unsigned long> assigned_cluster);
    visualization(int nbDim, int nbClus, std::vector< Eigen::MatrixXf > input_data, std::vector<unsigned long> assigned_cluster);
    void visualize();

private:
    std::vector< dlib::matrix<float> > _input_data;
    std::vector< Eigen::MatrixXf > _input_data_eigen;
    std::vector<unsigned long> _assigned_cluster;
    int _nbDim;
    int _nbClus;
};

#endif // VISUALIZATION_H
