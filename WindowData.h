#ifndef WINDOWDATA_H
#define WINDOWDATA_H

# include <QApplication>
# include <QWidget>
# include <QPushButton>
# include <QLCDNumber>
# include <QSlider>
# include <QMessageBox>
# include <QFileDialog>
# include <QLabel>
# include <QMainWindow>
#include <string>
#include <vector>

# include"WindowPara.h"

class WindowData : public QDialog
{
    Q_OBJECT

public:

    WindowData();
    QString getPathDataSet() const;
    QString getValueVariable() const;
    std::vector<int> size_csv(std::string path);
    void setSize(std::vector<int> size);
    void setPath(QString path);
    void setVariable(QString variable);
    void reopenPara();

public slots:
    void openHelp();
    void openBrowse();
    void openWindowPara();
    void openUpload();
    void openSelect();

private:

    QLabel *m_header;
    QLabel *m_browse;
    QLabel *m_browseSuccess;
    QLabel *m_select;
    QLabel *m_selectSuccess;
    QLabel *m_upload;
    QLabel *m_uploadSuccess;
    QLabel *m_title;

    QPushButton *m_buttonUpload;
    QPushButton *m_buttonNext;
    QPushButton *m_buttonQuit;
    QPushButton *m_buttonBrowse;
    QComboBox *m_buttonSelect;
    QPushButton *m_buttonHelp;

    QString m_pathDataSet;
    QString m_valueVariable;
    int firstItemSelect;

    std::vector<int> m_size;
};

#endif // WINDOWDATA_H
