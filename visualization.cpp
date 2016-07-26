#include "visualization.h"

#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkCellArray.h>
#include <vtkUnsignedCharArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkProperty.h>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>



visualization::visualization(int nbDim, int nbClus, std::vector< dlib::matrix<float> > input_data, std::vector<unsigned long> assigned_cluster): _nbDim(nbDim), _input_data(input_data), _assigned_cluster(assigned_cluster), _nbClus(nbClus)
{
}

visualization::visualization(int nbDim, int nbClus, std::vector< Eigen::MatrixXf > input_data, std::vector<unsigned long> assigned_cluster) : _nbDim(nbDim), _input_data_eigen(input_data), _assigned_cluster(assigned_cluster), _nbClus(nbClus)
{
}

void visualization::visualize()
{
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

    if(_nbDim == 2)
    {
        if(_input_data.size() > 0)
        {
            for(int i = 0; i < _input_data.size(); i++)
            {
                points->InsertNextPoint( _input_data[i](0,0),  _input_data[i](1,0), 0);
            }
        }
        else
        {
            for(int i = 0; i < _input_data_eigen.size(); i++)
            {
                points->InsertNextPoint( _input_data_eigen[i](0,0),  _input_data_eigen[i](1,0), 0);
            }
        }
    }
    else
    {
        if(_input_data.size() > 0)
        {
            for(int i = 0; i < _input_data.size(); i++)
            {
                points->InsertNextPoint( _input_data[i](0,0),  _input_data[i](1,0), _input_data[i](2,0));
            }
        }
        else
        {
            for(int i = 0; i < _input_data_eigen.size(); i++)
            {
                points->InsertNextPoint( _input_data_eigen[i](0,0),  _input_data_eigen[i](1,0), _input_data_eigen[i](2,0));
            }
        }
    }

    vtkSmartPointer<vtkPolyData> pointsPolydata = vtkSmartPointer<vtkPolyData>::New();
    pointsPolydata->SetPoints(points);

    vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter =vtkSmartPointer<vtkVertexGlyphFilter>::New();

#if VTK_MAJOR_VERSION <= 5
    vertexFilter->SetInputConnection(pointsPolydata->GetProducerPort());
#else
    vertexFilter->SetInputData(pointsPolydata);
#endif
    vertexFilter->Update();

    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
    polydata->ShallowCopy(vertexFilter->GetOutput());

    // Setup colors
    vtkSmartPointer<vtkUnsignedCharArray> colors = vtkSmartPointer<vtkUnsignedCharArray>::New();
    colors->SetNumberOfComponents(3);
    colors->SetName ("Colors");

    if(_input_data.size() > 0)
    {
        for(int i = 0; i < _input_data.size(); i++)
        {
            if(_assigned_cluster[i]%3 == 0)
            {
                unsigned char tempColor[3] = { (_assigned_cluster[i]+2)*255/_nbClus , 0 , 0};
                std::cout << "color r" << std::endl;
                std::cout << (_assigned_cluster[i]+2)*255/_nbClus << std::endl;
                colors->InsertNextTupleValue(tempColor);
            }
            else if(_assigned_cluster[i]%3 == 1)
            {
                unsigned char tempColor[3] = {0 , (_assigned_cluster[i]+2)*255/_nbClus , 0};
                std::cout << "color g" << std::endl;
                std::cout << (_assigned_cluster[i]+2)*255/_nbClus << std::endl;
                colors->InsertNextTupleValue(tempColor);
            }
            else if(_assigned_cluster[i]%3 == 2)
            {
                unsigned char tempColor[3] = {0 , 0 , (_assigned_cluster[i]+2)*255/_nbClus};
                colors->InsertNextTupleValue(tempColor);
            }
        }
    }
    else
    {
        unsigned char tempColor[3] = {255 , 0 , 0};
        for(int i = 0; i < _input_data_eigen.size(); i++)
        {
            colors->InsertNextTupleValue(tempColor);
        }
    }

    polydata->GetPointData()->SetScalars(colors);

    // Visualization
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
    mapper->SetInputConnection(polydata->GetProducerPort());
#else
    mapper->SetInputData(polydata);
#endif

    vtkSmartPointer<vtkActor> actor =  vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetPointSize(5);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderer->AddActor(actor);
    renderer->SetBackground(.2, .3, .4);

    vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
    vtkSmartPointer<vtkOrientationMarkerWidget> widget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    widget->SetOutlineColor( 0.9300, 0.5700, 0.1300 );
    widget->SetOrientationMarker( axes );
    widget->SetInteractor( renderWindowInteractor );
    widget->SetViewport( 0.0, 0.0, 0.4, 0.4 );
    widget->SetEnabled( 1 );

    renderWindow->Render();
    renderWindowInteractor->Start();
}
