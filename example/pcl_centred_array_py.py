# -*- coding: utf-8 -*-
from __future__ import print_function

import numpy as np
import pcl
import pcl.pcl_visualization


def main():
    cloud = pcl.load_XYZRGB('/home/zhao/processed.pcd')
    xyz_cloud = pcl.load('/home/zhao/processed.pcd')
    print(cloud.height, cloud.width, cloud[0])
    # Centred the data
    arr = xyz_cloud.to_array()
    # arr = arr[:, 0:3]
    centred = arr - np.mean(arr, 0)
    # print(np.mean(cloud, 0))
    ptcloud_centred = pcl.PointCloud()
    ptcloud_centred.from_array(centred)

    visual = pcl.pcl_visualization.CloudViewing()
    visual.ShowMonochromeCloud(ptcloud_centred, b'cloud')
    v = True
    while v:
        v = not (visual.WasStopped())


if __name__ == "__main__":
    main()

