# include "WindowData.h"
# include "WindowPara.h"
#include <sstream>
#include <fstream>
#include <iostream>

WindowData::WindowData() : QDialog()
{
     // Window

    setFixedSize(1200,800);
    setWindowIcon(QIcon("Cluster.png"));
    setWindowTitle("DataVisualizer 1.0");
    setObjectName("window");
    this->setStyleSheet("QWidget#window{background-image:url(Background.jpg);}");

    // Header

    m_header = new QLabel("<strong> DONNEES </strong> -  PARAMETRES - GRAPHIQUES", this);
    m_header->setFont(QFont("Arial",20));
    m_header->setStyleSheet("color:white");
    m_header->setGeometry(0, 50, 1200,40);
    m_header->setAlignment(Qt::AlignHCenter);

    // Title

    m_title = new QLabel(" Sélection des données\n ____________________________________________________________________________________ ", this);
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
    QObject::connect(m_buttonNext, SIGNAL(clicked()), this, SLOT(openWindowPara()));

    // Browse File

    m_browse = new QLabel("Veuillez sélectionner un fichier au format csv : ", this);
    m_browse->setFont(QFont("Arial",14, QFont::Bold));
    m_browse->setStyleSheet("color:white");
    m_browse->setGeometry(180, 300, 600,40);

    m_buttonBrowse = new QPushButton("Parcourir", this);
    m_buttonBrowse->setFont(QFont("Arial",14,QFont::Bold,false));
    m_buttonBrowse->setCursor(Qt::PointingHandCursor);
    m_buttonBrowse->setIcon(QIcon("Browse.png"));
    m_buttonBrowse->setToolTip("Séléctionner un fichier");
    m_buttonBrowse->setGeometry(870, 315, 150,40);
    m_buttonBrowse->setStyleSheet("color:white; border: 2px solid; border-radius : 10px; border-color: white; background-color : black");

    QObject::connect(m_buttonBrowse, SIGNAL(clicked()), this, SLOT(openBrowse()));

    m_browseSuccess = new QLabel("Le fichier a été correctement sélectionné", this);
    m_browseSuccess->setFont(QFont("Arial",12,-1, true));
    m_browseSuccess->setStyleSheet("color:white");
    m_browseSuccess->setGeometry(180, 330, 1000,40);
    m_browseSuccess->setHidden(true);

    // Select Variables

    m_select = new QLabel("Veuillez sélectionner les variables à considérer : ", this);
    m_select->setFont(QFont("Arial",14,QFont::Bold));
    m_select->setStyleSheet("color:white");
    m_select->setGeometry(180, 400, 600,40);

    m_buttonSelect = new QComboBox(this);
    m_buttonSelect->setFont(QFont("Arial",14,QFont::Bold,false));
    m_buttonSelect->setCursor(Qt::PointingHandCursor);
    m_buttonSelect->setToolTip("Sélectionner les variables");
    m_buttonSelect->setGeometry(870, 415, 150,40);
    m_buttonSelect->setStyleSheet("color:white; border: 2px solid; border-radius : 10px; border-color: white; background-color : black");
    m_buttonSelect->addItem("");
    m_buttonSelect->addItem("  Colonnes");
    m_buttonSelect->addItem("  Lignes");
    m_buttonSelect->setEnabled(false);

    int firstItemSelect = m_buttonSelect->findText("");
    qobject_cast<QStandardItemModel *>(m_buttonSelect->model())->item(firstItemSelect)->setEnabled(false);

    QObject::connect(m_buttonSelect, SIGNAL(currentTextChanged(QString)), this, SLOT(openSelect()));

    m_selectSuccess = new QLabel("Les variables ont été correctement sélectionnées", this);
    m_selectSuccess->setFont(QFont("Arial",12,-1, true));
    m_selectSuccess->setStyleSheet("color:white");
    m_selectSuccess->setGeometry(180, 430, 600,40);
    m_selectSuccess->setHidden(true);

    QObject::connect(m_buttonSelect, SIGNAL(currentTextChanged(QString)), m_selectSuccess, SLOT(show()));

    // Upload Data

    m_upload = new QLabel("Veuillez charger le fichier dans le programme : ", this);
    m_upload->setFont(QFont("Arial",14,QFont::Bold));
    m_upload->setStyleSheet("color:white");
    m_upload->setGeometry(180, 500, 600,40);

    m_buttonUpload = new QPushButton("Charger", this);
    m_buttonUpload->setFont(QFont("Arial",14,QFont::Bold,false));
    m_buttonUpload->setCursor(Qt::PointingHandCursor);
    m_buttonUpload->setIcon(QIcon("Upload.png"));
    m_buttonUpload->setToolTip("Charger le fichier sélectionné");
    m_buttonUpload->setGeometry(870, 515, 150,40);
    m_buttonUpload->setStyleSheet("color:white; border: 2px solid; border-radius : 10px; border-color: white; background-color : black");
    m_buttonUpload->setEnabled(false);

    QObject::connect(m_buttonUpload, SIGNAL(clicked()), this, SLOT(openUpload()));

    m_uploadSuccess = new QLabel("Le fichier et les variables ont été correctement chargés", this);
    m_uploadSuccess->setFont(QFont("Arial",12,-1, true));
    m_uploadSuccess->setStyleSheet("color:white; background-image:url()");
    m_uploadSuccess->setGeometry(180, 530, 600,40);
    m_uploadSuccess->setHidden(true);

    QObject::connect(m_buttonUpload, SIGNAL(clicked()), m_uploadSuccess, SLOT(show()));

}

// Access Methods

QString WindowData :: getPathDataSet() const
{
    return m_pathDataSet;
}

QString WindowData :: getValueVariable() const
{
    return m_valueVariable;
}


// Dialogs

void WindowData :: openHelp()
{
    QMessageBox::information(this, "Aide", "ETAPE n°1 : SELECTION DES DONNEES\n\n"
                                           "1. Cliquez sur Parcourir pour sélectionner le fichier à visualiser\n\n"
                                           "2. Indiquez si les variables sont les colonnes ou les lignes\n\n"
                                           "3. Cliquez sur Charger pour le charger dans le programme\n\n"
                                           "4. Cliquez sur Suivant pour passer à l'étape n°2\n");
}

void WindowData :: openBrowse()
{
    m_pathDataSet = QFileDialog::getOpenFileName(this, "Sélectionner un fichier",QString(), "Fichier csv (*.csv)");
    QMessageBox::information(this, "Fichier sélectionné", "Vous avez sélectionné : \n" + m_pathDataSet);
    m_buttonNext->setEnabled(false);

    if(m_pathDataSet!="")
    {
        m_buttonSelect->setEnabled(true);
        m_browseSuccess->setHidden(false);
    }
}

// Slots

void WindowData :: openSelect()
{
    m_valueVariable = m_buttonSelect->currentText();
    m_buttonNext->setEnabled(false);

    if(m_valueVariable!="")
    {
        m_buttonUpload->setEnabled(true);
        m_selectSuccess->setHidden(false);
    }
}

void WindowData :: openUpload()
{
    QMessageBox::information(this, "Chargement", "Vous avez chargé le fichier : \n" + m_pathDataSet +
                                                     "\n\net sélectionné les" + m_valueVariable + " pour variables");

    // Lancer l'algo de traitement du fichier csv
    // Afficher un message de succès à la place de m_uploadSuccess si l'algo de traitement a fonctionné

    m_buttonNext->setEnabled(true);
    m_uploadSuccess->setHidden(false);  
}

std::vector<int> WindowData::size_csv(std::string path) // permet de renvoyer la taille d'un tableau contenu dans un fichier csv
// Indiquer "path" le chemin et true si on veut le nombre de lignes et false si on veut le nombre de colonnes
{
    std::ifstream  data(path.c_str()); // on récupère le flux en lecture à partir du chemin du fichier
    std::string line; // on crée une string qui stockera une ligne l'une aprés l'autre
    int rows = 1; // variable d'itération sur les lignes
    int cols = 1; // variable d'itérations sur les colonnes

    while(std::getline(data,line))
    {
        std::stringstream  lineStream(line);
        std::string        cell;
        while(std::getline(lineStream,cell,','))
        {
            if( 0 <= int(cell.find("\r"))) //si retour à la ligne
            {
                cols++;
                cols = 1;
                rows++;
            }
            else
            {
                cols++; // on itère sur les colonnes
            }
        }
    }
   std::vector<int> size;
   size.push_back(rows);
   size.push_back(cols);
   return size;
}

void WindowData :: openWindowPara()
{
    m_size = size_csv(getPathDataSet().toUtf8().constData());
    std::string st = getValueVariable().toUtf8().constData();

    if(st == "  Colonnes")
    {
        int size_0 = m_size[0];
        m_size[0] = m_size[1];
        m_size[1] = size_0;
    }
    std::cout << m_size[0] << std::endl;
    std::cout << m_size[1] << std::endl;

    WindowPara *fenetrePara = new WindowPara(m_size);

    fenetrePara->setPathDataSet(getPathDataSet());
    fenetrePara->setValueVariable(getValueVariable());

    fenetrePara->exec();
}

void WindowData :: reopenPara()
{
    WindowPara *fenetrePara = new WindowPara(m_size);

    fenetrePara->setPathDataSet(getPathDataSet());
    fenetrePara->setValueVariable(getValueVariable());

    fenetrePara->exec();
}

void WindowData::setSize(std::vector<int> size)
{
    m_size = size;
}

void WindowData::setPath(QString path)
{
    m_pathDataSet = path;
}

void WindowData::setVariable(QString variable)
{
    m_valueVariable = variable;
}
