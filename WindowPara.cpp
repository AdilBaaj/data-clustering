# include "WindowPara.h"
# include "WindowData.h"
#include <sstream>
#include <fstream>
#include <datavisualizationprogram.h>
#include <iostream>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}


WindowPara::WindowPara(std::vector<int> size): QDialog(), m_size(size)
{
    // Window

    setFixedSize(1200,800);
    setWindowIcon(QIcon("Cluster.png"));
    setWindowTitle("DataVisualizer 1.0");
    setObjectName("window");
    this->setStyleSheet("QWidget#window{background-image:url(Background.jpg);}");

    // Header

    m_header = new QLabel(" DONNEES - <strong>PARAMETRES</strong> - GRAPHIQUES", this);
    m_header->setFont(QFont("Arial",20));
    m_header->setStyleSheet("color:white");
    m_header->setGeometry(0, 50, 1200,40);
    m_header->setAlignment(Qt::AlignHCenter);

    // Title

    m_title = new QLabel(" Traitement des données\n ____________________________________________________________________________________ ", this);
    m_title->setFont(QFont("Arial",16, QFont::Bold));
    m_title->setStyleSheet("color:white");
    m_title->setGeometry(20, 120, 1160,100);

    // Help

    m_buttonHelp = new QPushButton("Aide", this);
    m_buttonHelp->setFont(QFont("Arial",14,QFont::Bold,false));
    m_buttonHelp->setCursor(Qt::PointingHandCursor);
    m_buttonHelp->setToolTip("Demander de l'aide");
    m_buttonHelp->setGeometry(20, 740, 100,40);
    m_buttonHelp->setStyleSheet("color:white; border: 2px solid; border-radius : 10px; border-color: white; background-color : black");

    QObject::connect(m_buttonHelp, SIGNAL(clicked()), this, SLOT(openHelp()));

    // Cancel

    m_buttonQuit = new QPushButton("Annuler", this);
    m_buttonQuit->setFont(QFont("Arial",14,QFont::Bold,false));
    m_buttonQuit->setCursor(Qt::PointingHandCursor);
    m_buttonQuit->setToolTip("Quitter le programme");
    m_buttonQuit->setGeometry(1030, 740, 150,40);
    m_buttonQuit->setStyleSheet("color:white; border: 2px solid; border-radius : 10px; border-color: white; background-color : black");

    QObject::connect(m_buttonQuit, SIGNAL(clicked()), qApp, SLOT(quit()));

    // Next Step

    m_buttonNext = new QPushButton("Suivant", this);
    m_buttonNext->setFont(QFont("Arial",14,QFont::Bold,false));
    m_buttonNext->setCursor(Qt::PointingHandCursor);
    m_buttonNext->setIcon(QIcon("Next.png"));
    m_buttonNext->setToolTip("Etape suivante");
    m_buttonNext->setGeometry(870, 740, 150,40);
    m_buttonNext->setStyleSheet("color:white; border: 2px solid; border-radius : 10px; border-color: white; background-color : black");
    m_buttonNext->setEnabled(false);

    QObject::connect(m_buttonNext, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(m_buttonNext, SIGNAL(clicked()), this, SLOT(openWindowGraph()));

    // Previous Step

    m_buttonPrevious = new QPushButton("Précédent", this);
    m_buttonPrevious->setFont(QFont("Arial",14,QFont::Bold,false));
    m_buttonPrevious->setCursor(Qt::PointingHandCursor);
    m_buttonPrevious->setIcon(QIcon("Previous.png"));
    m_buttonPrevious->setToolTip("Etape précédente");
    m_buttonPrevious->setGeometry(710, 740, 150,40);
    m_buttonPrevious->setStyleSheet("color:white; border: 2px solid; border-radius : 10px; border-color: white; background-color : black");

    QObject::connect(m_buttonPrevious, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(m_buttonPrevious, SIGNAL(clicked()), this, SLOT(openWindowData()));

    // Upload

    m_buttonUpload = new QPushButton("Charger", this);
    m_buttonUpload->setFont(QFont("Arial",14,QFont::Bold,false));
    m_buttonUpload->setCursor(Qt::PointingHandCursor);
    m_buttonUpload->setToolTip("Appliquer ces paramètres");
    m_buttonUpload->setGeometry(150, 740, 150,40);
    m_buttonUpload->setStyleSheet("color:white; border: 2px solid; border-radius : 10px; border-color: white; background-color : black");
    //m_buttonUpload->setEnabled(false);

    QObject::connect(m_buttonUpload, SIGNAL(clicked()), this, SLOT(openUpload()));

    // Parameters : General

    m_textDataSet = new QLabel("<strong>Veuillez sélectionner les paramètres à utiliser : </strong>", this);
    m_textDataSet->setFont(QFont("Arial",14,-1, false));
    m_textDataSet->setStyleSheet("color:white");
    m_textDataSet->setGeometry(180, 225, 1000,40);

    // Parameters : Manual Algo

    paraManualBox = new QGroupBox ("Choix Manuel", this);

    paraManual2D = new QRadioButton("Classique 2D", this);
    paraManual2D->setFont(QFont("Arial",12,-1,false));
    paraManual2D->setChecked(true);

    QObject::connect(paraManual2D, SIGNAL(clicked(bool)), this, SLOT(choiceParaManual2D()));

    paraManual3D = new QRadioButton("Classique 3D", this);
    paraManual3D->setFont(QFont("Arial",12,-1,false));

    QObject::connect(paraManual3D, SIGNAL(clicked(bool)), this, SLOT(choiceParaManual3D()));

    paraManualQVBox = new QVBoxLayout;
    paraManualQVBox->addWidget(paraManual2D);
    paraManualQVBox->addWidget(paraManual3D);

    paraManualBox->setLayout(paraManualQVBox);
    paraManualBox->setStyleSheet("color:white");
    paraManualBox->setGeometry(180,275,840,200);
    paraManualBox->setFont(QFont("Arial",14,QFont::Bold,false));

    // Parameters : Auto Algo

    paraAutoBox = new QGroupBox ("Choix Automatique", this);

    paraAlgoKmeanLK = new QRadioButton("Kmean - Linear Kernel", this);
    paraAlgoKmeanLK->setFont(QFont("Arial",12,-1,false));

    QObject::connect(paraAlgoKmeanLK, SIGNAL(clicked(bool)), this, SLOT(choiceParaAutoKmeanLK()));

    paraAlgoKmeanPK = new QRadioButton("Kmean - Polynomial Kernel", this);
    paraAlgoKmeanPK->setFont(QFont("Arial",12,-1,false));

    QObject::connect(paraAlgoKmeanPK, SIGNAL(clicked(bool)), this, SLOT(choiceParaAutoKmeanPK()));

    paraAlgoKmeanRBK = new QRadioButton("Kmean - Radial Basis Kernel", this);
    paraAlgoKmeanRBK->setFont(QFont("Arial",12,-1,false));

    QObject::connect(paraAlgoKmeanRBK, SIGNAL(clicked(bool)), this, SLOT(choiceParaAutoKmeanRBK()));

    paraAlgoSpectralClustering = new QRadioButton("Spectral Clustering", this);
    paraAlgoSpectralClustering->setFont(QFont("Arial",12,-1,false));

    QObject::connect(paraAlgoSpectralClustering, SIGNAL(clicked(bool)), this, SLOT(choiceParaAutoSpectralClustering()));

    paraAutoQVBox = new QVBoxLayout;
    paraAutoQVBox->addWidget(paraAlgoKmeanLK);
    paraAutoQVBox->addWidget(paraAlgoKmeanPK);
    paraAutoQVBox->addWidget(paraAlgoKmeanRBK);
    paraAutoQVBox->addWidget(paraAlgoSpectralClustering);

    paraAutoBox->setLayout(paraAutoQVBox);
    paraAutoBox->setStyleSheet("color:white");
    paraAutoBox->setGeometry(180,500,840,200);
    paraAutoBox->setFont(QFont("Arial",14,QFont::Bold,false));

    // Para : Manual & Auto Exclusivity

    paraRadioButtonGroup = new QButtonGroup;
    paraRadioButtonGroup->addButton(paraManual2D);
    paraRadioButtonGroup->addButton(paraManual3D);
    paraRadioButtonGroup->addButton(paraAlgoKmeanLK);
    paraRadioButtonGroup->addButton(paraAlgoKmeanPK);
    paraRadioButtonGroup->addButton(paraAlgoKmeanRBK);
    paraRadioButtonGroup->addButton(paraAlgoSpectralClustering);

    // Parameters : Manual Classic 2D

    m_textVariable2D1 = new QLabel("v1 :", this);
    m_textVariable2D1 ->setFont(QFont("Arial",12,QFont::Bold, false));
    m_textVariable2D1 ->setStyleSheet("color:white");
    m_textVariable2D1 ->setGeometry(390, 344, 40, 25);

    m_variable2D1 = new QComboBox(this);
    m_variable2D1->setGeometry(440, 346, 100, 25);
    m_variable2D1->setStyleSheet("color:white; border: 2px solid; border-color: white; background-color : black");
    m_variable2D1->setCursor(Qt::PointingHandCursor);
    m_variable2D1->setToolTip("Choix de la première colonne");
    m_variable2D1->setEnabled(true);

    m_variable2D1->addItem("");

    for(int i = 0; i < m_size[0]; i++)
    {
        m_variable2D1->addItem(patch::to_string(i).c_str());
    }

    int firstItem2D1 = m_variable2D1->findText("");
    qobject_cast<QStandardItemModel *>(m_variable2D1->model())->item(firstItem2D1)->setEnabled(false);

    QObject::connect(m_variable2D1, SIGNAL(currentTextChanged(QString)), this, SLOT(changeVariable2D1()));

    m_textVariable2D2 = new QLabel("v2 :", this);
    m_textVariable2D2 ->setFont(QFont("Arial",12,QFont::Bold, false));
    m_textVariable2D2 ->setStyleSheet("color:white");
    m_textVariable2D2 ->setGeometry(624, 344, 40, 25);

    m_variable2D2 = new QComboBox(this);
    m_variable2D2->setGeometry(674, 346, 100, 25);
    m_variable2D2->setStyleSheet("color:white; border: 2px solid; border-color: white; background-color : black");
    m_variable2D2->setCursor(Qt::PointingHandCursor);
    m_variable2D2->setToolTip("Choix de la deuxième colonne");
    m_variable2D2->setEnabled(true);

    m_variable2D2->addItem("");
    for(int i = 0; i < m_size[0]; i++)
    {
         m_variable2D2->addItem(patch::to_string(i).c_str());
    }

    int firstItem2D2 = m_variable2D2->findText("");
    qobject_cast<QStandardItemModel *>(m_variable2D2->model())->item(firstItem2D2)->setEnabled(false);

    QObject::connect(m_variable2D2, SIGNAL(currentTextChanged(QString)), this, SLOT(changeVariable2D2()));

    // Parameters : Manual Classic 3D

    m_textVariable3D1 = new QLabel("v1 :", this);
    m_textVariable3D1 ->setFont(QFont("Arial",12,QFont::Bold, false));
    m_textVariable3D1 ->setStyleSheet("color:white");
    m_textVariable3D1 ->setGeometry(390, 406, 40, 25);

    m_variable3D1 = new QComboBox(this);
    m_variable3D1->setGeometry(440, 408, 100, 25);
    m_variable3D1->setStyleSheet("color:white; border: 2px solid; border-color: white; background-color : black");
    m_variable3D1->setCursor(Qt::PointingHandCursor);
    m_variable3D1->setToolTip("Choix de la première colonne");
    m_variable3D1->setEnabled(false);

    m_variable3D1->addItem("");
    for(int i = 0; i < m_size[0]; i++)
    {
         m_variable3D1->addItem(patch::to_string(i).c_str());
    }

    int firstItem3D1 = m_variable3D1->findText("");
    qobject_cast<QStandardItemModel *>(m_variable3D1->model())->item(firstItem3D1)->setEnabled(false);

    QObject::connect(m_variable3D1, SIGNAL(currentTextChanged(QString)), this, SLOT(changeVariable3D1()));

    m_textVariable3D2 = new QLabel("v2 :", this);
    m_textVariable3D2 ->setFont(QFont("Arial",12,QFont::Bold, false));
    m_textVariable3D2 ->setStyleSheet("color:white");
    m_textVariable3D2 ->setGeometry(624, 406, 40, 25);

    m_variable3D2 = new QComboBox(this);
    m_variable3D2->setGeometry(674, 408, 100, 25);
    m_variable3D2->setStyleSheet("color:white; border: 2px solid; border-color: white; background-color : black");
    m_variable3D2->setCursor(Qt::PointingHandCursor);
    m_variable3D2->setToolTip("Choix de la deuxième colonne");
    m_variable3D2->setEnabled(false);

    m_variable3D2->addItem("");
    for(int i = 0; i < m_size[0]; i++)
    {
         m_variable3D2->addItem(patch::to_string(i).c_str());
    }

    int firstItem3D2 = m_variable3D2->findText("");
    qobject_cast<QStandardItemModel *>(m_variable3D2->model())->item(firstItem3D2)->setEnabled(false);

    QObject::connect(m_variable3D2, SIGNAL(currentTextChanged(QString)), this, SLOT(changeVariable3D2()));

    m_textVariable3D3 = new QLabel("v3 :", this);
    m_textVariable3D3 ->setFont(QFont("Arial",12,QFont::Bold, false));
    m_textVariable3D3 ->setStyleSheet("color:white");
    m_textVariable3D3 ->setGeometry(858, 406, 40, 25);

    m_variable3D3=new QComboBox(this);
    m_variable3D3->setGeometry(908, 408, 100, 25);
    m_variable3D3->setStyleSheet("color:white; border: 2px solid; border-color: white; background-color : black");
    m_variable3D3->setCursor(Qt::PointingHandCursor);
    m_variable3D3->setToolTip("Choix de la troisième colonne");
    m_variable3D3->setEnabled(false);
    m_variable3D3->addItem("");

    for(int i = 0; i < m_size[0]; i++)
    {
         m_variable3D3->addItem(patch::to_string(i).c_str());
    }

    int firstItem3D3 = m_variable3D3->findText("");
    qobject_cast<QStandardItemModel *>(m_variable3D3->model())->item(firstItem3D3)->setEnabled(false);

    QObject::connect(m_variable3D3, SIGNAL(currentTextChanged(QString)), this, SLOT(changeVariable3D3()));

    // Parameters : Auto KmeanLK : Clusters & Variables

    m_textKmeanLKK = new QLabel("k :", this);
    m_textKmeanLKK ->setFont(QFont("Arial",12,QFont::Bold, false));
    m_textKmeanLKK ->setStyleSheet("color:white");
    m_textKmeanLKK ->setGeometry(485, 544, 25,25);

    m_sliderKmeanLKK = new QSlider(Qt::Horizontal, this);
    m_sliderKmeanLKK->setRange(2,20);
    m_sliderKmeanLKK->setGeometry(525, 548, 150, 25);
    m_sliderKmeanLKK->setFont(QFont("Arial",12,-1,false));
    m_sliderKmeanLKK->setCursor(Qt::PointingHandCursor);
    m_sliderKmeanLKK->setToolTip("Choix du nombre de clusters KmeanLK");
    m_sliderKmeanLKK->setEnabled(false);

    m_lcdKmeanLKK = new QLCDNumber(this);
    m_lcdKmeanLKK->setSegmentStyle(QLCDNumber::Filled);
    m_lcdKmeanLKK->setGeometry(685, 548, 50, 25);
    m_lcdKmeanLKK->setStyleSheet("color:white");

    QObject::connect(m_sliderKmeanLKK, SIGNAL(valueChanged(int)), m_lcdKmeanLKK, SLOT(display(int)));
    QObject::connect(m_sliderKmeanLKK, SIGNAL(sliderReleased()), this, SLOT(changeVariableKmeanLKK()));

    m_textKmeanLKC = new QLabel("v :", this);
    m_textKmeanLKC->setFont(QFont("Arial",12,QFont::Bold, false));
    m_textKmeanLKC->setStyleSheet("color:white");
    m_textKmeanLKC->setGeometry(758, 544, 25,25);

    m_sliderKmeanLKC = new QSlider(Qt::Horizontal, this);
    m_sliderKmeanLKC->setRange(2,3);
    m_sliderKmeanLKC->setGeometry(798, 548, 150, 25);
    m_sliderKmeanLKC->setFont(QFont("Arial",12,-1,false));
    m_sliderKmeanLKC->setCursor(Qt::PointingHandCursor);
    m_sliderKmeanLKC->setToolTip("Choix du nombre de variables KmeanLK");
    m_sliderKmeanLKC->setEnabled(false);

    m_lcdKmeanLKC = new QLCDNumber(this);
    m_lcdKmeanLKC->setSegmentStyle(QLCDNumber::Filled);
    m_lcdKmeanLKC->setGeometry(958, 548, 50, 25);
    m_lcdKmeanLKC->setStyleSheet("color:white");

    QObject::connect(m_sliderKmeanLKC, SIGNAL(valueChanged(int)), m_lcdKmeanLKC, SLOT(display(int))) ;
    QObject::connect(m_sliderKmeanLKC, SIGNAL(sliderReleased()), this, SLOT(changeVariableKmeanLKC()));

    // Parameters : Auto KmeanPK : Clusters & Variables

    m_textKmeanPKK = new QLabel("k :", this);
    m_textKmeanPKK ->setFont(QFont("Arial",12,QFont::Bold, false));
    m_textKmeanPKK ->setStyleSheet("color:white");
    m_textKmeanPKK ->setGeometry(485, 582, 25,25);

    m_sliderKmeanPKK = new QSlider(Qt::Horizontal, this);
    m_sliderKmeanPKK->setRange(2,20);
    m_sliderKmeanPKK->setGeometry(525, 586, 150, 25);
    m_sliderKmeanPKK->setFont(QFont("Arial",12,-1,false));
    m_sliderKmeanPKK->setCursor(Qt::PointingHandCursor);
    m_sliderKmeanPKK->setToolTip("Choix du nombre de clusters KmeanPK");
    m_sliderKmeanPKK->setEnabled(false);

    m_lcdKmeanPKK = new QLCDNumber(this);
    m_lcdKmeanPKK->setSegmentStyle(QLCDNumber::Filled);
    m_lcdKmeanPKK->setGeometry(685, 586, 50, 25);
    m_lcdKmeanPKK->setStyleSheet("color:white");

    QObject::connect(m_sliderKmeanPKK, SIGNAL(valueChanged(int)), m_lcdKmeanPKK, SLOT(display(int))) ;
    QObject::connect(m_sliderKmeanPKK, SIGNAL(sliderReleased()), this, SLOT(changeVariableKmeanPKK()));

    m_textKmeanPKC = new QLabel("v :", this);
    m_textKmeanPKC->setFont(QFont("Arial",12,QFont::Bold, false));
    m_textKmeanPKC->setStyleSheet("color:white");
    m_textKmeanPKC->setGeometry(758, 582, 25,25);

    m_sliderKmeanPKC = new QSlider(Qt::Horizontal, this);
    m_sliderKmeanPKC->setRange(2,3);
    m_sliderKmeanPKC->setGeometry(798, 586, 150, 25);
    m_sliderKmeanPKC->setFont(QFont("Arial",12,-1,false));
    m_sliderKmeanPKC->setCursor(Qt::PointingHandCursor);
    m_sliderKmeanPKC->setToolTip("Choix du nombre de variables KmeanPK");
    m_sliderKmeanPKC->setEnabled(false);

    m_lcdKmeanPKC = new QLCDNumber(this);
    m_lcdKmeanPKC->setSegmentStyle(QLCDNumber::Filled);
    m_lcdKmeanPKC->setGeometry(958, 586, 50, 25);
    m_lcdKmeanPKC->setStyleSheet("color:white");

    QObject::connect(m_sliderKmeanPKC, SIGNAL(valueChanged(int)), m_lcdKmeanPKC, SLOT(display(int))) ;
    QObject::connect(m_sliderKmeanPKC, SIGNAL(sliderReleased()), this, SLOT(changeVariableKmeanPKC()));

    // Parameters : Auto KmeanRBK : Clusters & Variables

    m_textKmeanRBKK = new QLabel("k :", this);
    m_textKmeanRBKK ->setFont(QFont("Arial",12,QFont::Bold, false));
    m_textKmeanRBKK ->setStyleSheet("color:white");
    m_textKmeanRBKK ->setGeometry(485, 620, 25,25);

    m_sliderKmeanRBKK = new QSlider(Qt::Horizontal, this);
    m_sliderKmeanRBKK->setRange(2,20);
    m_sliderKmeanRBKK->setGeometry(525, 624, 150, 25);
    m_sliderKmeanRBKK->setFont(QFont("Arial",12,-1,false));
    m_sliderKmeanRBKK->setCursor(Qt::PointingHandCursor);
    m_sliderKmeanRBKK->setToolTip("Choix du nombre de clusters KmeanRBK");
    m_sliderKmeanRBKK->setEnabled(false);

    m_lcdKmeanRBKK = new QLCDNumber(this);
    m_lcdKmeanRBKK->setSegmentStyle(QLCDNumber::Filled);
    m_lcdKmeanRBKK->setGeometry(685, 624, 50, 25);
    m_lcdKmeanRBKK->setStyleSheet("color:white");

    QObject::connect(m_sliderKmeanRBKK, SIGNAL(valueChanged(int)), m_lcdKmeanRBKK, SLOT(display(int))) ;
    QObject::connect(m_sliderKmeanRBKK, SIGNAL(sliderReleased()), this, SLOT(changeVariableKmeanRBKK()));

    m_textKmeanRBKC = new QLabel("v :", this);
    m_textKmeanRBKC->setFont(QFont("Arial",12,QFont::Bold, false));
    m_textKmeanRBKC->setStyleSheet("color:white");
    m_textKmeanRBKC->setGeometry(758, 620, 25,25);

    m_sliderKmeanRBKC = new QSlider(Qt::Horizontal, this);
    m_sliderKmeanRBKC->setRange(2,3);
    m_sliderKmeanRBKC->setGeometry(798, 624, 150, 25);
    m_sliderKmeanRBKC->setFont(QFont("Arial",12,-1,false));
    m_sliderKmeanRBKC->setCursor(Qt::PointingHandCursor);
    m_sliderKmeanRBKC->setToolTip("Choix du nombre de variables KmeanRBK");
    m_sliderKmeanRBKC->setEnabled(false);

    m_lcdKmeanRBKC = new QLCDNumber(this);
    m_lcdKmeanRBKC->setSegmentStyle(QLCDNumber::Filled);
    m_lcdKmeanRBKC->setGeometry(958, 624, 50, 25);
    m_lcdKmeanRBKC->setStyleSheet("color:white");

    QObject::connect(m_sliderKmeanRBKC, SIGNAL(valueChanged(int)), m_lcdKmeanRBKC, SLOT(display(int))) ;
    QObject::connect(m_sliderKmeanRBKC, SIGNAL(sliderReleased()), this, SLOT(changeVariableKmeanRBKC()));

    // Parameters : Auto Spectral Clustering : Clusters & Variables

    m_textSpectralClusteringK = new QLabel("k :", this);
    m_textSpectralClusteringK ->setFont(QFont("Arial",12,QFont::Bold, false));
    m_textSpectralClusteringK ->setStyleSheet("color:white");
    m_textSpectralClusteringK ->setGeometry(485, 658, 25,25);

    m_sliderSpectralClusteringK = new QSlider(Qt::Horizontal, this);
    m_sliderSpectralClusteringK->setRange(2,20);
    m_sliderSpectralClusteringK->setGeometry(525, 662, 150, 25);
    m_sliderSpectralClusteringK->setFont(QFont("Arial",12,-1,false));
    m_sliderSpectralClusteringK->setCursor(Qt::PointingHandCursor);
    m_sliderSpectralClusteringK->setToolTip("Choix du nombre de clusters SpectralClustering");
    m_sliderSpectralClusteringK->setEnabled(false);

    m_lcdSpectralClusteringK = new QLCDNumber(this);
    m_lcdSpectralClusteringK->setSegmentStyle(QLCDNumber::Filled);
    m_lcdSpectralClusteringK->setGeometry(685, 662, 50, 25);
    m_lcdSpectralClusteringK->setStyleSheet("color:white");

    QObject::connect(m_sliderSpectralClusteringK, SIGNAL(valueChanged(int)), m_lcdSpectralClusteringK, SLOT(display(int))) ;
    QObject::connect(m_sliderSpectralClusteringK, SIGNAL(sliderReleased()), this, SLOT(changeVariableSpectralClusteringK()));

    m_textSpectralClusteringC = new QLabel("v :", this);
    m_textSpectralClusteringC->setFont(QFont("Arial",12,QFont::Bold, false));
    m_textSpectralClusteringC->setStyleSheet("color:white");
    m_textSpectralClusteringC->setGeometry(758, 658, 25,25);

    m_sliderSpectralClusteringC = new QSlider(Qt::Horizontal, this);
    m_sliderSpectralClusteringC->setRange(2,3);
    m_sliderSpectralClusteringC->setGeometry(798, 662, 150, 25);
    m_sliderSpectralClusteringC->setFont(QFont("Arial",12,-1,false));
    m_sliderSpectralClusteringC->setCursor(Qt::PointingHandCursor);
    m_sliderSpectralClusteringC->setToolTip("Choix du nombre de variables SpectralClustering");
    m_sliderSpectralClusteringC->setEnabled(false);

    m_lcdSpectralClusteringC = new QLCDNumber(this);
    m_lcdSpectralClusteringC->setSegmentStyle(QLCDNumber::Filled);
    m_lcdSpectralClusteringC->setGeometry(958, 662, 50, 25);
    m_lcdSpectralClusteringC->setStyleSheet("color:white");

    QObject::connect(m_sliderSpectralClusteringC, SIGNAL(valueChanged(int)), m_lcdSpectralClusteringC, SLOT(display(int))) ;
    QObject::connect(m_sliderSpectralClusteringC, SIGNAL(sliderReleased()), this, SLOT(changeVariableSpectralClusteringC()));

    // Paramaters : Initialization

    m_valueVariable2D1 = -1;
    m_valueVariable2D2 = -1;
    m_valueVariable3D1 = -1;
    m_valueVariable3D2 = -1;
    m_valueVariable3D3 = -1;

    m_valueKmeanLKK = -1;
    m_valueKmeanLKC = -1;
    m_valueKmeanPKK = -1;
    m_valueKmeanPKC = -1;
    m_valueKmeanRBKK = -1;
    m_valueKmeanRBKC = -1;
    m_valueSpectralClusteringK = -1;
    m_valueSpectralClusteringC = -1;

    m_lcdKmeanLKK->display(2);
    m_lcdKmeanLKC->display(2);
    m_lcdKmeanPKK->display(2);
    m_lcdKmeanPKC->display(2);
    m_lcdKmeanRBKK->display(2);
    m_lcdKmeanRBKC->display(2);
    m_lcdSpectralClusteringK->display(2);
    m_lcdSpectralClusteringC->display(2);
}

// Access Methods

void WindowPara :: setPathDataSet(QString path)
{
    m_pathDataSet = path;
}

void WindowPara :: setValueVariable(QString value)
{
    m_valueVariable = value;
}

// Dialogs

void WindowPara :: openHelp()
{
    QMessageBox::information(this, "Aide", "ETAPE n°2 : TRAITEMENT DES DONNEES\n\n"
                                           "1. Choisissez un mode de visualisation parmi :\n"
                                           " - Classique 2D\n"
                                           " - Classique 3D\n"
                                           " - Clustering & PCA : Kmean Linear Kernel\n"
                                           " - Clustering & PCA : Kmean Polynomial Kernel\n"
                                           " - Clustering & PCA : Kmean Radial Basis Kernel\n"
                                           " - Clustering & PCA : Kmean Spectral Clustering\n\n"
                                           "2. Si vous avez sélectionné Classique 2D / 3D :\n"
                                           " Choisissez les numéros des variables à visualiser\n\n"
                                           "3. Si vous avez sélectionné Clustering & PCA :\n"
                                           " Choisissez le nombre de clusters et de variables\n\n"
                                           "4. Cliquer sur Suivant pour passer à l'étape n°3\n");
}

void WindowPara :: openUpload()
{
    // Para List Setup

    m_para.clear();

    m_para.insert(0,m_valueVariable2D1);
    m_para.insert(1,m_valueVariable2D2);
    m_para.insert(2,m_valueVariable3D1);
    m_para.insert(3,m_valueVariable3D2);
    m_para.insert(4,m_valueVariable3D3);
    m_para.insert(5,m_valueKmeanLKK);
    m_para.insert(6,m_valueKmeanLKC);
    m_para.insert(7,m_valueKmeanPKK);
    m_para.insert(8,m_valueKmeanPKC);
    m_para.insert(9,m_valueKmeanRBKK);
    m_para.insert(10,m_valueKmeanRBKC);
    m_para.insert(11,m_valueSpectralClusteringK);
    m_para.insert(12,m_valueSpectralClusteringC);

    // Para List Display

    m_paraQString ="";

    for(int i=0; i<m_para.size(); i++)
    {
        m_paraQString += QString::number(m_para[i]);
        if (i<m_para.size()-1)
        {
            m_paraQString += " , " ;
        }
    }

    // Para List Integrity Check

    m_counter=0;

    for(int i=0; i<m_para.size(); i++)
    {
        if (m_para[i]!=-1)
        {
            m_counter += 1;
        }
    }

    if ((m_counter==3) || (m_counter==2 && m_para[2]==-1 && m_para[3]==-1 && m_para[4]==-1))
    {
        QMessageBox::information(this, "Paramètres Chargés",    "Vous avez chargé ces paramètres :"
                                                            "\n\n - Manuel Classique 2D v1 : " + QString::number(m_valueVariable2D1) +
                                                            "\n - Manuel Classique 2D v2 : " + QString::number(m_valueVariable2D2) +
                                                            "\n - Manuel Classique 3D v1 : " + QString::number(m_valueVariable3D1) +
                                                            "\n - Manuel Classique 3D v2 : " + QString::number(m_valueVariable3D2) +
                                                            "\n - Manuel Classique 3D v3 : " + QString::number(m_valueVariable3D3) +
                                                            "\n\n - Automatique Kmean LK k : " + QString::number(m_valueKmeanLKK) +
                                                            "\n - Automatique Kmean LK v : " + QString::number(m_valueKmeanLKC) +
                                                            "\n - Automatique Kmean PK k : " + QString::number(m_valueKmeanPKK) +
                                                            "\n - Automatique Kmean PK v : " + QString::number(m_valueKmeanPKC) +
                                                            "\n - Automatique Kmean RBK k : " + QString::number(m_valueKmeanRBKK) +
                                                            "\n - Automatique Kmean RBK v : " + QString::number(m_valueKmeanRBKC) +
                                                            "\n - Automatique Spectral Clustering k : " + QString::number(m_valueSpectralClusteringK) +
                                                            "\n - Automatique Spectral Clustering v : " + QString::number(m_valueSpectralClusteringC)+
                                                            "\n\nRappel :" +
                                                            "\n\n - Fichier :" + m_pathDataSet +
                                                            "\n\n - Variables : " + m_valueVariable +
                                                            "\n\nRésumé :\n" + m_paraQString +
                                                            "\n\nNB : la valeur par défault des variables est -1.");

        // Lancer l'algo correspondant au choix de l'utilisateur
        // Afficher un message de succès si l'algo a fonctionné

        m_buttonNext->setEnabled(true);
    }

    else
    {
        QMessageBox::warning(this, "Chargement", "Vous avez oublié de renseigner un paramètre !\n\n"
                                                 "NB : Si vous souhaitez sélectionner la valeur affichée par défault (2) pour k et v, "
                                                 "veillez à cliquer sur le curseur de la barre pour valider cette valeur.");
    }
}

// Algo Choice Slots (QRadioButton)

void WindowPara :: choiceParaManual2D()
{
    // Display Reset

    m_buttonNext->setEnabled(false);

    m_variable2D1->setCurrentText("");
    m_variable2D2->setCurrentText("");
    m_variable3D1->setCurrentText("");
    m_variable3D2->setCurrentText("");
    m_variable3D3->setCurrentText("");

    m_sliderKmeanLKK->setSliderPosition(2);
    m_sliderKmeanLKC->setSliderPosition(2);
    m_sliderKmeanPKK->setSliderPosition(2);
    m_sliderKmeanPKC->setSliderPosition(2);
    m_sliderKmeanRBKK->setSliderPosition(2);
    m_sliderKmeanRBKC->setSliderPosition(2);
    m_sliderSpectralClusteringK->setSliderPosition(2);
    m_sliderSpectralClusteringC->setSliderPosition(2);

    // Value Reset

    m_valueVariable2D1 = -1;
    m_valueVariable2D2 = -1;
    m_valueVariable3D1 = -1;
    m_valueVariable3D2 = -1;
    m_valueVariable3D3 = -1;

    m_valueKmeanLKK=-1;
    m_valueKmeanLKC=-1;
    m_valueKmeanPKK=-1;
    m_valueKmeanPKC=-1;
    m_valueKmeanRBKK=-1;
    m_valueKmeanRBKC=-1;
    m_valueSpectralClusteringK=-1;
    m_valueSpectralClusteringC=-1;

    // Enabled Buttons Setup

    m_variable2D1->setEnabled(true);
    m_variable2D2->setEnabled(true);
    m_variable3D1->setEnabled(false);
    m_variable3D2->setEnabled(false);
    m_variable3D3->setEnabled(false);
    m_sliderKmeanLKK->setEnabled(false);
    m_sliderKmeanLKC->setEnabled(false);
    m_sliderKmeanPKK->setEnabled(false);
    m_sliderKmeanPKC->setEnabled(false);
    m_sliderKmeanRBKK->setEnabled(false);
    m_sliderKmeanRBKC->setEnabled(false);
    m_sliderSpectralClusteringK->setEnabled(false);
    m_sliderSpectralClusteringC->setEnabled(false);
}

void WindowPara :: choiceParaManual3D()
{
    // Display Reset

    m_buttonNext->setEnabled(false);

    m_variable2D1->setCurrentText("");
    m_variable2D2->setCurrentText("");
    m_variable3D1->setCurrentText("");
    m_variable3D2->setCurrentText("");
    m_variable3D3->setCurrentText("");

    m_sliderKmeanLKK->setSliderPosition(2);
    m_sliderKmeanLKC->setSliderPosition(2);
    m_sliderKmeanPKK->setSliderPosition(2);
    m_sliderKmeanPKC->setSliderPosition(2);
    m_sliderKmeanRBKK->setSliderPosition(2);
    m_sliderKmeanRBKC->setSliderPosition(2);
    m_sliderSpectralClusteringK->setSliderPosition(2);
    m_sliderSpectralClusteringC->setSliderPosition(2);

    // Value Reset

    m_valueVariable2D1 = -1;
    m_valueVariable2D2 = -1;
    m_valueVariable3D1 = -1;
    m_valueVariable3D2 = -1;
    m_valueVariable3D3 = -1;

    m_valueKmeanLKK=-1;
    m_valueKmeanLKC=-1;
    m_valueKmeanPKK=-1;
    m_valueKmeanPKC=-1;
    m_valueKmeanRBKK=-1;
    m_valueKmeanRBKC=-1;
    m_valueSpectralClusteringK=-1;
    m_valueSpectralClusteringC=-1;

    // Enabled Buttons Setup

    m_sliderKmeanLKK->setSliderPosition(2);
    m_sliderKmeanLKC->setSliderPosition(2);
    m_sliderKmeanPKK->setSliderPosition(2);
    m_sliderKmeanPKC->setSliderPosition(2);
    m_sliderKmeanRBKK->setSliderPosition(2);
    m_sliderKmeanRBKC->setSliderPosition(2);
    m_sliderSpectralClusteringK->setSliderPosition(2);
    m_sliderSpectralClusteringC->setSliderPosition(2);
    m_variable2D1->setEnabled(false);
    m_variable2D2->setEnabled(false);
    m_variable3D1->setEnabled(true);
    m_variable3D2->setEnabled(true);
    m_variable3D3->setEnabled(true);
    m_sliderKmeanLKK->setEnabled(false);
    m_sliderKmeanLKC->setEnabled(false);
    m_sliderKmeanPKK->setEnabled(false);
    m_sliderKmeanPKC->setEnabled(false);
    m_sliderKmeanRBKK->setEnabled(false);
    m_sliderKmeanRBKC->setEnabled(false);
    m_sliderSpectralClusteringK->setEnabled(false);
    m_sliderSpectralClusteringC->setEnabled(false);
}

void WindowPara :: choiceParaAutoKmeanLK()
{
    // Display Reset

    m_buttonNext->setEnabled(false);

    m_variable2D1->setCurrentText("");
    m_variable2D2->setCurrentText("");
    m_variable3D1->setCurrentText("");
    m_variable3D2->setCurrentText("");
    m_variable3D3->setCurrentText("");

    m_sliderKmeanLKK->setSliderPosition(2);
    m_sliderKmeanLKC->setSliderPosition(2);
    m_sliderKmeanPKK->setSliderPosition(2);
    m_sliderKmeanPKC->setSliderPosition(2);
    m_sliderKmeanRBKK->setSliderPosition(2);
    m_sliderKmeanRBKC->setSliderPosition(2);
    m_sliderSpectralClusteringK->setSliderPosition(2);
    m_sliderSpectralClusteringC->setSliderPosition(2);

    // Value Reset

    m_valueVariable2D1 = -1;
    m_valueVariable2D2 = -1;
    m_valueVariable3D1 = -1;
    m_valueVariable3D2 = -1;
    m_valueVariable3D3 = -1;

    m_valueKmeanLKK=-1;
    m_valueKmeanLKC=-1;
    m_valueKmeanPKK=-1;
    m_valueKmeanPKC=-1;
    m_valueKmeanRBKK=-1;
    m_valueKmeanRBKC=-1;
    m_valueSpectralClusteringK=-1;
    m_valueSpectralClusteringC=-1;

    // Enabled Buttons Setup

    m_variable2D1->setEnabled(false);
    m_variable2D2->setEnabled(false);
    m_variable3D1->setEnabled(false);
    m_variable3D2->setEnabled(false);
    m_variable3D3->setEnabled(false);
    m_sliderKmeanLKK->setEnabled(true);
    m_sliderKmeanLKC->setEnabled(true);
    m_sliderKmeanPKK->setEnabled(false);
    m_sliderKmeanPKC->setEnabled(false);
    m_sliderKmeanRBKK->setEnabled(false);
    m_sliderKmeanRBKC->setEnabled(false);
    m_sliderSpectralClusteringK->setEnabled(false);
    m_sliderSpectralClusteringC->setEnabled(false);
}

void WindowPara :: choiceParaAutoKmeanPK()
{
    // Display Reset

    m_buttonNext->setEnabled(false);

    m_variable2D1->setCurrentText("");
    m_variable2D2->setCurrentText("");
    m_variable3D1->setCurrentText("");
    m_variable3D2->setCurrentText("");
    m_variable3D3->setCurrentText("");

    m_sliderKmeanLKK->setSliderPosition(2);
    m_sliderKmeanLKC->setSliderPosition(2);
    m_sliderKmeanPKK->setSliderPosition(2);
    m_sliderKmeanPKC->setSliderPosition(2);
    m_sliderKmeanRBKK->setSliderPosition(2);
    m_sliderKmeanRBKC->setSliderPosition(2);
    m_sliderSpectralClusteringK->setSliderPosition(2);
    m_sliderSpectralClusteringC->setSliderPosition(2);

    // Value Reset

    m_valueVariable2D1 = -1;
    m_valueVariable2D2 = -1;
    m_valueVariable3D1 = -1;
    m_valueVariable3D2 = -1;
    m_valueVariable3D3 = -1;

    m_valueKmeanLKK=-1;
    m_valueKmeanLKC=-1;
    m_valueKmeanPKK=-1;
    m_valueKmeanPKC=-1;
    m_valueKmeanRBKK=-1;
    m_valueKmeanRBKC=-1;
    m_valueSpectralClusteringK=-1;
    m_valueSpectralClusteringC=-1;

    // Enabled Buttons Setup

    m_variable2D1->setEnabled(false);
    m_variable2D2->setEnabled(false);
    m_variable3D1->setEnabled(false);
    m_variable3D2->setEnabled(false);
    m_variable3D3->setEnabled(false);
    m_sliderKmeanLKK->setEnabled(false);
    m_sliderKmeanLKC->setEnabled(false);
    m_sliderKmeanPKK->setEnabled(true);
    m_sliderKmeanPKC->setEnabled(true);
    m_sliderKmeanRBKK->setEnabled(false);
    m_sliderKmeanRBKC->setEnabled(false);
    m_sliderSpectralClusteringK->setEnabled(false);
    m_sliderSpectralClusteringC->setEnabled(false);
}

void WindowPara :: choiceParaAutoKmeanRBK()
{
    // Display Reset

    m_buttonNext->setEnabled(false);

    m_variable2D1->setCurrentText("");
    m_variable2D2->setCurrentText("");
    m_variable3D1->setCurrentText("");
    m_variable3D2->setCurrentText("");
    m_variable3D3->setCurrentText("");

    m_sliderKmeanLKK->setSliderPosition(2);
    m_sliderKmeanLKC->setSliderPosition(2);
    m_sliderKmeanPKK->setSliderPosition(2);
    m_sliderKmeanPKC->setSliderPosition(2);
    m_sliderKmeanRBKK->setSliderPosition(2);
    m_sliderKmeanRBKC->setSliderPosition(2);
    m_sliderSpectralClusteringK->setSliderPosition(2);
    m_sliderSpectralClusteringC->setSliderPosition(2);

    // Value Reset

    m_valueVariable2D1 = -1;
    m_valueVariable2D2 = -1;
    m_valueVariable3D1 = -1;
    m_valueVariable3D2 = -1;
    m_valueVariable3D3 = -1;

    m_valueKmeanLKK=-1;
    m_valueKmeanLKC=-1;
    m_valueKmeanPKK=-1;
    m_valueKmeanPKC=-1;
    m_valueKmeanRBKK=-1;
    m_valueKmeanRBKC=-1;
    m_valueSpectralClusteringK=-1;
    m_valueSpectralClusteringC=-1;

    // Enabled Buttons Setup

    m_variable2D1->setEnabled(false);
    m_variable2D2->setEnabled(false);
    m_variable3D1->setEnabled(false);
    m_variable3D2->setEnabled(false);
    m_variable3D3->setEnabled(false);
    m_sliderKmeanLKK->setEnabled(false);
    m_sliderKmeanLKC->setEnabled(false);
    m_sliderKmeanPKK->setEnabled(false);
    m_sliderKmeanPKC->setEnabled(false);
    m_sliderKmeanRBKK->setEnabled(true);
    m_sliderKmeanRBKC->setEnabled(true);
    m_sliderSpectralClusteringK->setEnabled(false);
    m_sliderSpectralClusteringC->setEnabled(false);
}

void WindowPara :: choiceParaAutoSpectralClustering()
{
    // Display Reset

    m_buttonNext->setEnabled(false);

    m_variable2D1->setCurrentText("");
    m_variable2D2->setCurrentText("");
    m_variable3D1->setCurrentText("");
    m_variable3D2->setCurrentText("");
    m_variable3D3->setCurrentText("");

    m_sliderKmeanLKK->setSliderPosition(2);
    m_sliderKmeanLKC->setSliderPosition(2);
    m_sliderKmeanPKK->setSliderPosition(2);
    m_sliderKmeanPKC->setSliderPosition(2);
    m_sliderKmeanRBKK->setSliderPosition(2);
    m_sliderKmeanRBKC->setSliderPosition(2);
    m_sliderSpectralClusteringK->setSliderPosition(2);
    m_sliderSpectralClusteringC->setSliderPosition(2);

    // Value Reset

    m_valueVariable2D1 = -1;
    m_valueVariable2D2 = -1;
    m_valueVariable3D1 = -1;
    m_valueVariable3D2 = -1;
    m_valueVariable3D3 = -1;

    m_valueKmeanLKK=-1;
    m_valueKmeanLKC=-1;
    m_valueKmeanPKK=-1;
    m_valueKmeanPKC=-1;
    m_valueKmeanRBKK=-1;
    m_valueKmeanRBKC=-1;
    m_valueSpectralClusteringK=-1;
    m_valueSpectralClusteringC=-1;

    // Enabled Buttons Setup

    m_variable2D1->setEnabled(false);
    m_variable2D2->setEnabled(false);
    m_variable3D1->setEnabled(false);
    m_variable3D2->setEnabled(false);
    m_variable3D3->setEnabled(false);
    m_sliderKmeanLKK->setEnabled(false);
    m_sliderKmeanLKC->setEnabled(false);
    m_sliderKmeanPKK->setEnabled(false);
    m_sliderKmeanPKC->setEnabled(false);
    m_sliderKmeanRBKK->setEnabled(false);
    m_sliderKmeanRBKC->setEnabled(false);
    m_sliderSpectralClusteringK->setEnabled(true);
    m_sliderSpectralClusteringC->setEnabled(true);
}

// Variables Setups Slots (QComboBox & QSlider)

void WindowPara :: changeVariable2D1()
{
    m_buttonNext->setEnabled(false);
    m_valueVariable2D1 = m_variable2D1->currentIndex();
}

void WindowPara :: changeVariable2D2()
{
    m_buttonNext->setEnabled(false);
    m_valueVariable2D2 = m_variable2D2->currentIndex();
}

void WindowPara :: changeVariable3D1()
{
    m_buttonNext->setEnabled(false);
    m_valueVariable3D1 = m_variable3D1->currentIndex();
}

void WindowPara :: changeVariable3D2()
{
    m_buttonNext->setEnabled(false);
    m_valueVariable3D2 = m_variable3D2->currentIndex();
}

void WindowPara :: changeVariable3D3()
{
    m_buttonNext->setEnabled(false);
    m_valueVariable3D3 = m_variable3D3->currentIndex();
}

void WindowPara :: changeVariableKmeanLKK()
{
    m_buttonNext->setEnabled(false);
    m_valueKmeanLKK = m_sliderKmeanLKK->value();
}

void WindowPara :: changeVariableKmeanLKC()
{
    m_buttonNext->setEnabled(false);
    m_valueKmeanLKC = m_sliderKmeanLKC->value();
}

void WindowPara :: changeVariableKmeanPKK()
{
    m_buttonNext->setEnabled(false);
    m_valueKmeanPKK = m_sliderKmeanPKK->value();
}

void WindowPara :: changeVariableKmeanPKC()
{
    m_buttonNext->setEnabled(false);
    m_valueKmeanPKC = m_sliderKmeanPKC->value();
}

void WindowPara :: changeVariableKmeanRBKK()
{
    m_buttonNext->setEnabled(false);
    m_valueKmeanRBKK = m_sliderKmeanRBKK->value();
}

void WindowPara :: changeVariableKmeanRBKC()
{
    m_buttonNext->setEnabled(false);
    m_valueKmeanRBKC = m_lcdKmeanRBKC->value();
}

void WindowPara :: changeVariableSpectralClusteringK()
{
    m_buttonNext->setEnabled(false);
    m_valueSpectralClusteringK = m_sliderSpectralClusteringK->value();
}

void WindowPara :: changeVariableSpectralClusteringC()
{
    m_buttonNext->setEnabled(false);
    m_valueSpectralClusteringC = m_sliderSpectralClusteringC->value();
}

// Windows Opening Slots (QPushButton Previous & Next)

void WindowPara :: openWindowData()
{
    WindowData *fenetreData = new WindowData();
    fenetreData->exec();
}

void WindowPara :: openWindowGraph()
{
    Datavisualizationprogram program(m_para, m_size, m_valueVariable, m_pathDataSet);
    program.run();

    WindowData *fenetreData = new WindowData();
    fenetreData->setSize(m_size);
    fenetreData->setPath(m_pathDataSet);
    fenetreData->setVariable(m_valueVariable);
    fenetreData->openWindowPara();
}
