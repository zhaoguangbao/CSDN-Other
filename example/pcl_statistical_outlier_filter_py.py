import pcl


def main():
    p = pcl.load("/home/zhao/unprocessed.pcd")

    fil = p.make_statistical_outlier_filter()
    fil.set_mean_k(50)
    fil.set_std_dev_mul_thresh(1.0)

    pcl.save(fil.filter(),
             "/home/zhao/unprocessed_inliers.pcd")

    fil.set_negative(True)
    pcl.save(fil.filter(),
             "/home/zhao/unprocessed_outliers.pcd")


if __name__ == "__main__":
    main()

