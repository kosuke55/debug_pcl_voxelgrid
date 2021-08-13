# debug_pcl_voxelgrid
For https://github.com/PointCloudLibrary/pcl/issues/4895

```
cd build
cmake ..
make
./main 2.0 2.0 2.0
# sudo snap install cloudcompare
cloudcompare.CloudCompare input.pcd downsampled.pcd restored.pcd
```

Video: https://user-images.githubusercontent.com/39142679/129369754-225cd3a2-3273-4e90-ab91-c3f4cead9378.mp4  
The red point cloud is a downsample. There is a point cloud in a strange position on the right side. In addition, there is a defect in the point cloud restored from the map with the downsampled point cloud and the original point cloud.
