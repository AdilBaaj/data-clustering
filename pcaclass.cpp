#include "pcaclass.h"

#include <iostream>
#include <vector>

#include <Eigen/Dense>
#include <Eigen/Eigenvalues>


Pcaclass::Pcaclass()
{

}

Pcaclass::Pcaclass(int nbVariables, int nbRecords,  const Eigen::MatrixXf& inputData) : _nbVariables(nbVariables), _nbRecords(nbRecords), _inputData(inputData)
{
    _transformedData.resize(_nbVariables, _nbRecords);
    _eigenVec.resize(_nbVariables, _nbVariables);
    _eigenValues.resize(_nbVariables, 1);
    _varMat.resize(_nbVariables, _nbVariables);
}

void Pcaclass::runPCA()
{
    //Substract mean of each variable

    for(int i = 0; i < _inputData.rows(); i++)
    {
        float mean = 0;

        for(int j = 0; j < _inputData.cols(); j++)
        {
            mean += _inputData(i,j);
        }

        mean /= _nbRecords;

        for(int j = 0; j < _inputData.cols(); j++)
        {
            _transformedData(i,j) = _inputData(i,j) - mean;
            std::cout << _transformedData(i,j) << std::endl;
        }
    }

    //Compute covariance matrix
    _varMat = 1/float(_nbVariables) * _transformedData * _transformedData.transpose();

    //Diagonalization of covariance matrix

    Eigen::JacobiSVD<Eigen::MatrixXf> svd(_varMat, Eigen::ComputeThinU | Eigen::ComputeThinV);
    _eigenVec = svd.matrixU();
    _eigenValues = svd.singularValues();

    //Compute principal components

    for(int i = 0; i < _nbVariables; i++)
    {
        _principalComponents.push_back(_transformedData.transpose() * _eigenVec.col(i));
    }

    //Compute decomposition of vector data on eigen vector basis
    //std::cout << _eigenVec * transformedData.col(0) << std::endl;
}

std::vector<Eigen::MatrixXf> Pcaclass::projectDataOnEigVec(int nbdimtokeep)
{
    std::vector<Eigen::MatrixXf> listprojectedData;
    for(int i = 0; i < _transformedData.cols(); i++)
    {
        Eigen::MatrixXf projectedData(nbdimtokeep, 1);
        
        for(int j = 0; j < nbdimtokeep; j++)
        {
            projectedData(j,0) = _eigenVec.col(j).transpose() * _transformedData.col(i);
            std::cout << _transformedData.col(i) << std::endl;
            std::cout << projectedData(j,0) << std::endl;
            std::cout << _eigenVec.col(j).transpose() << std::endl;
        }
        listprojectedData.push_back(projectedData);
    }
    
    return listprojectedData;
}

Eigen::MatrixXf Pcaclass::get_inputData()
{
    return _inputData;
}
Eigen::MatrixXf Pcaclass::get_transformedData()
{
    return _transformedData;
}
Eigen::MatrixXf Pcaclass::get_eigenVec()
{
    return _eigenVec;
}
Eigen::MatrixXf Pcaclass::get_eigenValues()
{
    return _eigenValues;
}
Eigen::MatrixXf Pcaclass::get_varMat()
{
    return _varMat;
}
std::vector< Eigen::MatrixXf >  Pcaclass::get_principalComponents()
{
    return _principalComponents;
}
