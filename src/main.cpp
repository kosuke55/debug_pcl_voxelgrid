#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "pcl/filters/filter.h"
#include "pcl/filters/voxel_grid.h"
#include "pcl/io/pcd_io.h"
#include "pcl/pcl_base.h"
#include "pcl/point_types.h"

int main(int argc, char* argv[]) {
  float voxel_size_x = atoi(argv[1]);
  float voxel_size_y = atoi(argv[2]);
  float voxel_size_z = atoi(argv[3]);

  pcl::VoxelGrid<pcl::PointXYZRGB> voxel_grid;
  voxel_grid.setLeafSize(voxel_size_x, voxel_size_y, voxel_size_z);
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
  pcl::io::loadPCDFile("input.pcd", *cloud);
  voxel_grid.setInputCloud(cloud);
  voxel_grid.setSaveLeafLayout(true);
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr downsampled_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
  voxel_grid.filter(*downsampled_cloud);
  std::unordered_map<int, pcl::PointCloud<pcl::PointXYZRGB>> downsampled2restored_map;
  for (auto& point : cloud->points) {
    const int index = voxel_grid.getCentroidIndex(point);
    downsampled2restored_map[index].points.push_back(point);
  }

  pcl::PointCloud<pcl::PointXYZRGB>::Ptr restored_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
  for (auto& point : downsampled_cloud->points) {
    point.r = 255;
    point.g = 0;
    point.b = 0;
    const int index = voxel_grid.getCentroidIndex(point);
    for (const auto& restored_point : downsampled2restored_map[index].points) {
      restored_cloud->points.push_back(restored_point);
    }
  }
  *cloud += *downsampled_cloud;
  restored_cloud->width = restored_cloud->size();
  restored_cloud->height = 1;

  pcl::io::savePCDFileASCII("downsampled.pcd", *downsampled_cloud);
  pcl::io::savePCDFileASCII("restored.pcd", *restored_cloud);

  return 0;
}
