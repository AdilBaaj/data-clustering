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
/*
    //fenetreData.getPathDataSet();
   std::vector<int> inputParams(14);
   inputParams[0] = 1;
   inputParams[1] = -1;
   inputParams[2] = -1;
   inputParams[3] = -1;
   inputParams[4] = 0;
   inputParams[5] = 5;
   inputParams[6] = 8;
   inputParams[7] = 3;
   inputParams[8] = 3;
   inputParams[9] = 1;
   inputParams[10] = -1;
   inputParams[11] = -1;
   inputParams[12] = -1;
   inputParams[13] = 1;

   std::string path = "/Users/Adil/Desktop/test3.csv";
   Datavisualizationprogram program(inputParams, path);
   program.run();
   return 0;
   */

   return app.exec();
}


