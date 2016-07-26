#ifndef WINDOWPARA_H
#define WINDOWPARA_H

# include <QApplication>
# include <QWidget>
# include <QPushButton>
# include <QLCDNumber>
# include <QSlider>
# include <QMessageBox>
# include <QFileDialog>
# include <QLabel>
# include <QtWidgets>
# include "WindowData.h"
#include <vector>

class WindowPara : public QDialog
{

    Q_OBJECT

public:

    WindowPara(std::vector<int> size);

    void setPathDataSet(QString path);
    void setValueVariable(QString value);

public slots:

    void openHelp();
    void openUpload();
    void openWindowData();
    void openWindowGraph();

    void choiceParaManual2D();
    void changeVariable2D1();
    void changeVariable2D2();

    void choiceParaManual3D();
    void changeVariable3D1();
    void changeVariable3D2();
    void changeVariable3D3();

    void choiceParaAutoKmeanLK();
    void changeVariableKmeanLKK();
    void changeVariableKmeanLKC();

    void choiceParaAutoKmeanPK();
    void changeVariableKmeanPKK();
    void changeVariableKmeanPKC();

    void choiceParaAutoKmeanRBK();
    void changeVariableKmeanRBKK();
    void changeVariableKmeanRBKC();

    void choiceParaAutoSpectralClustering();
    void changeVariableSpectralClusteringK();
    void changeVariableSpectralClusteringC();

private:

    // General

    QLabel *m_header;
    QLabel *m_title;
    QLabel *m_browse;
    QLabel *m_browseSuccess;
    QLabel *m_upload;
    QLabel *m_textDataSet;

    QPushButton *m_buttonQuit;
    QPushButton *m_buttonNext;
    QPushButton *m_buttonBrowse;
    QPushButton *m_buttonHelp;
    QPushButton *m_buttonUpload;
    QPushButton *m_buttonPrevious;

    // Para Manual

    QVBoxLayout *paraQVBox;

    QGroupBox *paraManualBox;
    QRadioButton *paraManual2D;
    QRadioButton *paraManual3D;
    QVBoxLayout *paraManualQVBox;

    QLabel *m_textVariable2D1;
    QComboBox *m_variable2D1;
    int m_valueVariable2D1;
    int firstItem2D1;

    QLabel *m_textVariable2D2;
    QComboBox *m_variable2D2;
    int m_valueVariable2D2;
    int firstItem2D2;

    QLabel *m_textVariable3D1;
    QComboBox *m_variable3D1;
    int m_valueVariable3D1;
    int firstItem3D1;

    QLabel *m_textVariable3D2;
    QComboBox *m_variable3D2;
    int m_valueVariable3D2;
    int firstItem3D2;

    QLabel *m_textVariable3D3;
    QComboBox *m_variable3D3;
    int m_valueVariable3D3;
    int firstItem3D3;

    // Para Auto

    QGroupBox *paraAutoBox;
    QRadioButton *paraAlgoKmeanLK;
    QRadioButton *paraAlgoKmeanPK;
    QRadioButton *paraAlgoKmeanRBK;
    QRadioButton *paraAlgoSpectralClustering;
    QVBoxLayout *paraAutoQVBox;

    QLabel *m_textKmeanLKK;
    QLCDNumber *m_lcdKmeanLKK;
    int m_valueKmeanLKK;
    QSlider *m_sliderKmeanLKK;
    QLabel *m_textKmeanLKC;
    QLCDNumber *m_lcdKmeanLKC;
    int m_valueKmeanLKC;
    QSlider *m_sliderKmeanLKC;

    QLabel *m_textKmeanPKK;
    QLCDNumber *m_lcdKmeanPKK;
    int m_valueKmeanPKK;
    QSlider *m_sliderKmeanPKK;
    QLabel *m_textKmeanPKC;
    QLCDNumber *m_lcdKmeanPKC;
    int m_valueKmeanPKC;
    QSlider *m_sliderKmeanPKC;

    QLabel *m_textKmeanRBKK;
    QLCDNumber *m_lcdKmeanRBKK;
    int m_valueKmeanRBKK;
    QSlider *m_sliderKmeanRBKK;
    QLabel *m_textKmeanRBKC;
    QLCDNumber *m_lcdKmeanRBKC;
    int m_valueKmeanRBKC;
    QSlider *m_sliderKmeanRBKC;

    QLabel *m_textSpectralClusteringK;
    QLCDNumber *m_lcdSpectralClusteringK;
    int m_valueSpectralClusteringK;
    QSlider *m_sliderSpectralClusteringK;
    QLabel *m_textSpectralClusteringC;
    QLCDNumber *m_lcdSpectralClusteringC;
    int m_valueSpectralClusteringC;
    QSlider *m_sliderSpectralClusteringC;

    QButtonGroup *paraRadioButtonGroup;

    // Para General

    QString m_pathDataSet;
    QString m_valueVariable;
    QList<int> m_para;

    // Others

    QString m_paraQString;
    int m_counter;
    int m_nb_records;
    std::vector<int> m_size;
};

#endif // WINDOWPARA_H
