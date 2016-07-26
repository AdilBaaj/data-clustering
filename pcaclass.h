#ifndef PCACLASS_H
#define PCACLASS_H

#include <Eigen/Dense>
#include <vector>

class Pcaclass
{
public:
    Pcaclass();
    Pcaclass(int nbVariables, int nbRecords,  const Eigen::MatrixXf& inputData);
    void runPCA();
    std::vector<Eigen::MatrixXf> projectDataOnEigVec(int nbdimtokeep);
    
    Eigen::MatrixXf get_inputData();
    Eigen::MatrixXf get_transformedData();
    Eigen::MatrixXf get_eigenVec();
    Eigen::MatrixXf get_eigenValues();
    Eigen::MatrixXf get_varMat();
    std::vector< Eigen::MatrixXf >  get_principalComponents();
    
private:
    Eigen::MatrixXf _inputData;
    Eigen::MatrixXf _transformedData;
    Eigen::MatrixXf _eigenVec;
    Eigen::MatrixXf _eigenValues;
    Eigen::MatrixXf _varMat;
    std::vector< Eigen::MatrixXf >  _principalComponents;
    
    int _nbRecords;
    int _nbVariables;   
};

#endif // PCACLASS_H
