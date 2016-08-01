#include "clusteringclass.h"
#include <dlib/clustering.h>

Clusteringclass::Clusteringclass()
{

}

Clusteringclass::Clusteringclass(int init_nb_dim, int k_clusters, int method, std::vector< dlib::matrix<float> >& input_data) :  _init_nb_dim(init_nb_dim), _k_clusters(k_clusters), _method(method), _input_data(input_data)
{

}

void Clusteringclass::runClustering()
{
    if (_method == 0)
    {
        linear_kmean();
    }
    else if (_method == 1)
    {
        poly_kmean();
    }
    else if (_method == 2)
    {
        radial_basis_kmean();
    }
    else if (_method == 3)
    {
        spectral_clustering();
    }
}

void Clusteringclass::linear_kmean()
{
    typedef dlib::matrix<float> sample_type;
    typedef dlib::linear_kernel<sample_type> kernel_type;

    typedef dlib::linear_kernel<sample_type> kernel_type;

    dlib::kcentroid< kernel_type > kc;
    dlib::kkmeans< kernel_type > kmean(kc);
    std::vector<sample_type> initial_centers;

    // Tell the kkmeans object we made that we want to run k-means with k_clusters sets
    kmean.set_number_of_centers(_k_clusters);

    // You need to pick some initial centers for the k-means algorithm.  So here
    // we will use the dlib::pick_initial_centers() function which tries to find
    // n points that are far apart (basically).
    pick_initial_centers(_k_clusters, initial_centers, _input_data, kmean.get_kernel());

    //Now run the k-means algorithm on our set of samples.
    kmean.train(_input_data, initial_centers);

    //Now loop over all our samples and get their predicted class.
    for (unsigned long i = 0; i < _input_data.size(); ++i)
    {
        _assigned_cluster.push_back(kmean(_input_data[i]));
    }
}

void Clusteringclass::poly_kmean()
{
    typedef dlib::matrix<float> sample_type;
    typedef dlib::polynomial_kernel<sample_type> kernel_type;

    dlib::kcentroid< kernel_type > kc;
    dlib::kkmeans< kernel_type > kmean(kc);
    std::vector<sample_type> initial_centers;

    // tell the kkmeans object we made that we want to run k-means with k_clusters sets
    kmean.set_number_of_centers(_k_clusters);

    // You need to pick some initial centers for the k-means algorithm.  So here
    // we will use the dlib::pick_initial_centers() function which tries to find
    // n points that are far apart (basically).
    pick_initial_centers(_k_clusters, initial_centers, _input_data, kmean.get_kernel());

    // now run the k-means algorithm on our set of samples.
    kmean.train(_input_data, initial_centers);

    // now loop over all our samples and get their predicted class.
    for (unsigned long i = 0; i < _input_data.size(); ++i)
    {
        _assigned_cluster.push_back(kmean(_input_data[i]));
    }
}

void Clusteringclass::radial_basis_kmean()
{
    typedef dlib::matrix<float> sample_type;
    typedef dlib::radial_basis_kernel<sample_type> kernel_type;

    dlib::kcentroid< kernel_type > kc;
    dlib::kkmeans< kernel_type > kmean(kc);
    std::vector<sample_type> initial_centers;

    // tell the kkmeans object we made that we want to run k-means with k_clusters sets
    kmean.set_number_of_centers(_k_clusters);

    // You need to pick some initial centers for the k-means algorithm.  So here
    // we will use the dlib::pick_initial_centers() function which tries to find
    // n points that are far apart (basically).
    pick_initial_centers(_k_clusters, initial_centers, _input_data, kmean.get_kernel());

    // now run the k-means algorithm on our set of samples.
    kmean.train(_input_data, initial_centers);

    // now loop over all our samples and get their predicted class.
    for (unsigned long i = 0; i < _input_data.size(); ++i)
    {
        _assigned_cluster.push_back(kmean(_input_data[i]));
        std::cout << _input_data[i] << std::endl;
        std::cout << _assigned_cluster[i] << std::endl;
    }
}

void Clusteringclass::spectral_clustering()
{
    typedef dlib::matrix<float> sample_type;
    typedef dlib::radial_basis_kernel<sample_type> kernel_type;

    //Perform spectral clustering
    _assigned_cluster = spectral_cluster(kernel_type(0.1), _input_data, 3);
}

std::vector< unsigned long > Clusteringclass::get_assigned_cluster()
{
    return _assigned_cluster;
}



