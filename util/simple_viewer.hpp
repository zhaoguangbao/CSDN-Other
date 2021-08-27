#include <Eigen/Dense>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

template <typename T>
bool checkRGBFields(const std::string& fields)
{
    std::vector<pcl::PCLPointField> fields_;
    bool capable_=false;
    int field_idx_ = pcl::getFieldIndex<T> (fields, fields_);
    if (field_idx_ != -1)
    {
        capable_ = true;
    }
    return capable_;
}

/* color: custom color*/
template <typename T>
typename pcl::visualization::PCLVisualizer::Ptr simpleViewer(typename pcl::PointCloud<T>::ConstPtr cloud,
                                                             const Eigen::Vector3i& color=Eigen::Vector3i::Ones(),
                                                             pcl::PointCloud<pcl::Normal>::ConstPtr normals=nullptr)
{
    pcl::visualization::PCLVisualizer::Ptr viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
    viewer->setBackgroundColor (0, 0, 0);
    bool capable_=false;
    capable_= checkRGBFields<T>("rgb") || checkRGBFields<T>("rgba");
    bool custom_color_=(color!=Eigen::Vector3i::Ones());
    std::string cloud_id;
    if(custom_color_) // use custom color
    {
        cloud_id="custom_cloud";
        pcl::visualization::PointCloudColorHandlerCustom<T> cloud_color(cloud, color(0), color(1), color(2));
        viewer->addPointCloud(cloud, cloud_color, cloud_id);
    }else if(!capable_) // no rgb fields and custom color
    {
        cloud_id="original_cloud";
        viewer->addPointCloud<T> (cloud, cloud_id);
    }
    else // no custom_color and with rgb filed
    {
        cloud_id="rgb_cloud";
        pcl::visualization::PointCloudColorHandlerRGBField<T> rgb(cloud);
        viewer->addPointCloud<T> (cloud, rgb, cloud_id);
    }
    viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, cloud_id);
    if(normals)
        viewer->addPointCloudNormals<T, pcl::Normal> (cloud, normals, 10, 0.05, "normals");
    viewer->addCoordinateSystem (0.1);
    viewer->initCameraParameters ();
    return (viewer);
}
