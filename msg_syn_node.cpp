#include <ros/ros.h>
#include <message_filters/subscriber.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/Image.h>

using namespace sensor_msgs;
using namespace message_filters;

void callback(const ImageConstPtr& image, const ImuConstPtr& imu_data)
{
  // Procesa los datos sincronizados aquí...
  ROS_INFO("Synchronized messages received");
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "messages_syn");

  ros::NodeHandle nh;

  message_filters::Subscriber<Image> image_sub(nh, "image", 1);
  message_filters::Subscriber<Imu> imu_data_sub(nh, "imu_data", 1);

  typedef sync_policies::ApproximateTime<Image, Imu> MySyncPolicy;
  Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), image_sub, imu_data_sub);

  sync.registerCallback(boost::bind(&callback, _1, _2));

  ros::spin();

  return 0;
}
