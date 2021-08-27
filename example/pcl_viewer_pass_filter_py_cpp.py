# -*- coding: utf-8 -*-
import pcl
import pcl.pcl_visualization


# viewer type 2
def vis():
    visual = pcl.pcl_visualization.CloudViewing()

    # expected pcl._pcl.PointCloud <--> pcl.load()
    # visual.ShowMonochromeCloud(cloud, b'cloud')

    # expected pcl._pcl.PointCloud_PointXYZI <--> pcl.load_XYZI()
    # visual.ShowGrayCloud(cloud, b'cloud')

    # expected pcl._pcl.PointCloud_PointXYZRGB <--> pcl.load_XYZRGB()
    # visual.ShowColorCloud(cloud, b'cloud')

    # expected pcl._pcl.PointCloud_PointXYZRGBA <--> pcl.load_XYZRGBA()
    # visual.ShowColorACloud(cloud, b'cloud')

    v = True
    while v:
        v = not (visual.WasStopped())


# viewer type 1
def main():
    # pcl::visualization::PCLVisualizer viewer ("Simple visualizing window");
    viewer = pcl.pcl_visualization.PCLVisualizering()

    # pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGBA>);
    # pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZRGBA>);
    # pcl::io::loadPLYFile<pcl::PointXYZRGBA> (argv[1], *cloud) //* load the ply file from command line
    cloud = pcl.load("/home/zhao/processed.pcd")
    # cloud = pcl.load("textured.obj")

    # pcl::copyPointCloud(*cloud,*cloud_filtered);
    # cloud_filtered = cloud.copyPointCloud()
    cloud_filtered = cloud

    # Applying passthrough filters with XYZ limits: same with x, y, z field
    # pcl::PassThrough<pcl::PointXYZRGBA> pass;
    # pass.setInputCloud(cloud);
    # pass.setFilterFieldName ("y");
    # pass.setFilterLimits (-0.1, 0.1);
    # pass.filter(*cloud);
    pass_th = cloud.make_passthrough_filter()
    pass_th.set_filter_field_name("y")
    pass_th.set_filter_limits(0, 0.1)
    cloud = pass_th.filter()

    viewer.AddPointCloud(cloud, b'scene_cloud', 0)
    viewer.AddCoordinateSystem(0.1)
    # viewer.RemovePointCloud(b'scene_cloud', 0)
    while not viewer.WasStopped():
        viewer.Spin()


if __name__ == "__main__":
    main()

