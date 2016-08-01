#ifndef DATAVISUALIZATIONPROGRAM_H
#define DATAVISUALIZATIONPROGRAM_H

#include <vector>
#include <string>
# include <QApplication>


class Datavisualizationprogram
{
public:
    Datavisualizationprogram();
    Datavisualizationprogram(QList<int> inputParams, std::vector<int> size, QString valueVariable ,QString path);
    void run();

private:

    int m_auto;
    int m_manuel;
    int m_kpca;
    int m_kclus;
    int m_c2d_1;
    int m_c2d_2;
    int m_c3d_1;
    int m_c3d_2;
    int m_c3d_3;
    int m_linearKmean;
    int m_polynomialKmean;
    int m_radialbasisKmean;
    int m_spectralClustering;
    QList<int> m_inputParams;
    std::string m_varAreCol;
    std::string m_path;
    unsigned long m_nb_rows;
    unsigned long m_nb_cols;
};

#endif
