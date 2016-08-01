#include "datavisualizationprogram.h"
#include <clusteringclass.h>
#include <pcaclass.h>
#include <data.h>
#include <dataset.h>
#include <visualization.h>

//Assert permet d'arreter le code en cas d'erreur lors des test unitaire
#include <assert.h>

Datavisualizationprogram::Datavisualizationprogram()
{

}

Datavisualizationprogram::Datavisualizationprogram(QList<int> inputParams, std::vector<int> size, QString valueVariable ,QString path)

{
    m_path = path.toUtf8().constData();;//string
    
    // Test Unitaire n.8:

            if(m_path.length()<=0)
                    {
                    std::cout << "Erreur : Test Unitaire 8 Échoué" ;
                    assert (1==1);
                    }
    
    m_auto = std::max(inputParams[5],std::max(inputParams[7],std::max(inputParams[9], inputParams[11])));; //int
    m_manuel  = std::max(inputParams[0], inputParams[2]); //int
    
    // Test Unitaire n.9:

            if(m_auto>-1 && m_manuel>-1)
                
                    {
                    std::cout << "Erreur : Test Unitaire 9 Échoué" ;
                    assert (1==1);
                    }
    
            else if(m_auto<=-1 && m_manuel<=-1)
                    {
                    std::cout << "Erreur : Test Unitaire 9 Échoué" ;
                    assert (1==1);
                    }
            
     
    
    m_c2d_1 = inputParams[0]; //int
    m_c2d_2 = inputParams[1]; //int
    m_c3d_1 = inputParams[2]; //int
    m_c3d_2 = inputParams[3]; //int
    m_c3d_3 = inputParams[4]; //int
    m_kpca =  std::max(inputParams[12],std::max(inputParams[10],std::max(inputParams[6], inputParams[8]))); //int
    m_kclus = std::max(inputParams[5],std::max(inputParams[7],std::max(inputParams[9], inputParams[11]))); //int
    m_linearKmean = inputParams[5]; //int
    m_polynomialKmean = inputParams[7]; //int
    m_radialbasisKmean = inputParams[9]; //int
    m_spectralClustering = inputParams[11]; //int
    m_varAreCol = valueVariable.toUtf8().constData(); //std::string
    if(m_varAreCol == "  Colonnes")
    {
        m_nb_rows  = size[1];
        m_nb_cols = size[0];
    }
    
   // Test Unitaire n.1
    
    if(m_nb_rows<=0 || m_nb_cols<=0)
    {
        std::cout << "Erreur : Test Unitaire 1 Échoué" ;
        assert (1==1);
    }
    
    
    // Test Unitaire n.10:

 if(m_c2d_1<0 || m_c2d_2<0 || m_c3d_1<0 || m_c3d_2<0 || m_c3d_3<0)
                    {
                    std::cout << "Erreur : Test Unitaire 10 Échoué" ;
                    assert (1==1);
                    }
 else if (m_c2d_1>m_nb_rows || m_c2d_2>m_nb_rows || m_c3d_1>m_nb_rows || m_c3d_2>m_nb_rows || m_c3d_3>m_nb_rows)
                    {
                    std::cout << "Erreur : Test Unitaire 10 Échoué" ;
                    assert (1==1);
                    }
    
    
   
    

}

void Datavisualizationprogram::run()
{
    //Put dataset into an Eigen::MatrixXf
    Dataset dataset(m_path, m_nb_rows, m_nb_cols);
    
    Eigen::MatrixXf tempinputData(dataset.get_nb_rows(), dataset.get_nb_columns());
    
    
    
    // Test Unitaire n.2:
    
    if(tempinputData.size()<=0)
    {
        std::cout << "Erreur : Test Unitaire 2 Échoué" ;
        assert (1==1);
    }
    
    
    
    
    for(int i = 0; i < tempinputData.rows(); i++)
    {
        for(int j = 0; j < tempinputData.cols(); j++)
        {
            tempinputData(i,j) = dataset.get_element(i,j);
        }
    }
    Eigen::MatrixXf inputData;
    if(m_varAreCol == "  Colonnes")
    {
        inputData.resize(tempinputData.cols(), tempinputData.rows());
        inputData = tempinputData.transpose();
    }
    else
    {
        inputData.resize(tempinputData.rows(), tempinputData.cols());
        inputData = tempinputData;
        //bla = inputData;
    }

    
    
    
    // Test Unitaire n.3:
    
    if(inputData.size()<=0)
    {
        std::cout << "Erreur : Test Unitaire 3 Échoué" ;
        assert (1==1);
    }
    
    
    
    
    std::cout << inputData << std::endl;
    
    //If user chooses manuel processing of data
    if(m_manuel > -1)
    {
        std::vector<Eigen::MatrixXf> listData;
        if(m_c2d_1 > -1)
        {
            Eigen::MatrixXf manualData(2, 1);
            for(int i = 0; i < inputData.cols(); i++)
            {
                manualData(0,0) = inputData(m_c2d_1, i);
                manualData(1,0) = inputData(m_c2d_2, i);
                listData.push_back(manualData);
            }
           
            // Test Unitaire n.4:
            
            if(listData.size()<=0)
            {
                std::cout << "Erreur : Test Unitaire 4 Échoué" ;
                assert (1==1);
            }
            
            std::vector<unsigned long> a;
            a.push_back(1);
            visualization visualizationObject(2, 1, listData, a);
            visualizationObject.visualize();
        }
        else
        {
            std::vector<Eigen::MatrixXf> listData;
            Eigen::MatrixXf manualData(3, 1);
            for(int i = 0; i < inputData.cols(); i++)
            {
                manualData(0,0) = inputData(m_c3d_1, i);
                manualData(1,0) = inputData(m_c3d_2, i);
                manualData(2,0) = inputData(m_c3d_3, i);
                listData.push_back(manualData);
            }
            
            // Test Unitaire n.5:
            
            if(listData.size()<=0)
            {
                std::cout << "Erreur : Test Unitaire 5  Échoué" ;
                assert (1==1);
            }
            
            
            std::vector<unsigned long> a;
            a.push_back(1);
            visualization visualizationObject(3, 1, listData, a);
            visualizationObject.visualize();
        }

    }
    
    //If user choses automatic processing of data
    if(m_auto > -1)
        
    {
        
        // Test Unitaire n.11:
    
     if(m_kpca<=-1 && m_kclus <=-1 && m_linearKmean <=-1 && m_polynomialKmean<=-1 && m_radialbasisKmean<=-1 && m_spectralClustering <=-1)
                        {
                        std::cout << "Erreur : Test Unitaire 11 Échoué" ;
                        assert (1==1);
                        }
    
        
        
        
        
        
        
        
        Pcaclass pca(inputData.rows(), inputData.cols(), inputData);
        pca.runPCA();

        std::vector<Eigen::MatrixXf> listprojecteddata = pca.projectDataOnEigVec(m_kpca);
        
               // Test Unitaire n.6:
        
        if(listprojecteddata.size()<=0)
        {
            std::cout << "Erreur : Test Unitaire 6 Échoué" ;
            assert (1==1);
        }

        int method = 0;
        
        if(m_linearKmean > -1)
        {
            method = 0;
        }
        else if (m_polynomialKmean > -1)
        {
            method = 1;
        }
        else if (m_radialbasisKmean > -1)
        {
            method = 2;
        }
        else
        {
            method = 3;
        }

        std::vector< dlib::matrix<float> > input_data_Clustering;

        for(int i = 0; i < listprojecteddata.size(); i++)
        {
            input_data_Clustering.push_back(dlib::mat(listprojecteddata[i]));
        }

        // Test Unitaire n.7:
 
 if(input_data_Clustering.size()<=0)
 {
     std::cout << "Erreur : Test Unitaire 7 Échoué" ;
     assert (1==1);
 }
        
        Clusteringclass cluster(input_data_Clustering[0].nr(), m_kclus, method, input_data_Clustering);
        cluster.runClustering();

        visualization visualizationObject(3, 2, input_data_Clustering, cluster.get_assigned_cluster());
        visualizationObject.visualize();
    }
}

