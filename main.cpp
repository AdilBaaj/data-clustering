# include <QApplication>
# include <QtWidgets>
# include "WindowData.h"
# include "WindowPara.h"
#include <datavisualizationprogram.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    WindowData fenetreData;
    fenetreData.show();
    return app.exec();
}


