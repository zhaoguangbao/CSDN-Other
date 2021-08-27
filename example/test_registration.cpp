//
// Created by zhao on 2021/8/16.
//

#include <pcl/point_cloud.h>
#include <pcl/registration/icp.h>
#include <random>

template <class Scalar>
Scalar my_rand_f()
{
    std::default_random_engine generator;
    std::uniform_real_distribution <Scalar> distribution(0.0, 1.0);
    return distribution(generator);
}

int main()
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out(new pcl::PointCloud<pcl::PointXYZ>);
    cloud_in->width=5;
    cloud_in->height   = 1;
    cloud_in->is_dense = false;
    cloud_in->points.resize (cloud_in->width * cloud_in->height);

    const float temp_max=1024.0;
    for (auto & point : cloud_in->points)
    {
        point.x = 1024 * my_rand_f<float>() / (temp_max + 1.0f);
        point.y = 1024 * my_rand_f<float>() / (temp_max + 1.0f);
        point.z = 1024 * my_rand_f<float>() / (temp_max + 1.0f);
    }

    pcl::copyPointCloud(*cloud_in, *cloud_out);
//    for (size_t i = 0; i < cloud_in->points.size (); ++i)
//        cloud_out->points[i].x += 0.7f;

    pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
    icp.setInputCloud(cloud_in);
    icp.setInputTarget(cloud_out);
    pcl::PointCloud<pcl::PointXYZ> Final;
    icp.align(Final);
    std::cout << "has converged:" << icp.hasConverged() << " score: " << icp.getFitnessScore() << std::endl;
    std::cout << icp.getFinalTransformation() << std::endl;
    return 0;
}

