#ifndef CLUSTERINGCLASS_H
#define CLUSTERINGCLASS_H

#include <vector>
#include <dlib/matrix.h>

class Clusteringclass
{
public:
    Clusteringclass();

    // method = 0 : Linear Kernel; method = 1 : polynomial Kernel; method = 2 : radial basis kernel; method = 3 :
    Clusteringclass(int init_nb_dim, int k_clusters, int method, std::vector< dlib::matrix<float> >& input_data);
    void runClustering();
    std::vector< unsigned long > get_assigned_cluster();

private:
    void linear_kmean();
    void poly_kmean();
    void radial_basis_kmean();
    void spectral_clustering();

private:
    std::vector< dlib::matrix<float> > _input_data;
    std::vector< unsigned long > _assigned_cluster;
    int _init_nb_dim;
    int _k_clusters;
    int _nb_samples;
    int _method;
};

#endif // CUSTERINGCLASS_H
