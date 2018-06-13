#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>

double pick_pos = 2.0;
double pick_ori = 1.0;
double drop_pos = 3.5;
double drop_ori = 2.0;
double threshold = 0.25;
double alpha = 1.0;

double pos = pick_pos;
double ori = pick_ori;



void odomCallback(const nav_msgs::Odometry::ConstPtr &msg) {

  //ROS_INFO("test");
    //ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  //ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  //ros::Subscriber sub = n.subscribe("odom", 1000, odomCallback);
  //ros::Subscriber odom_sub = n.subscribe("/odom", 1000, odomCallback);
// %EndTag(INIT)%

  // Set our initial shape type to be a cube
// %Tag(SHAPE_INIT)%
  uint32_t shape = visualization_msgs::Marker::CUBE;
// %EndTag(SHAPE_INIT)%
  

// %Tag(MARKER_INIT)%
//  while (ros::ok())
//  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();
// %EndTag(MARKER_INIT)%

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
// %Tag(NS_ID)%
    marker.ns = "add_markers";
    marker.id = 0;
// %EndTag(NS_ID)%

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
// %Tag(TYPE)%
    marker.type = shape;
// %EndTag(TYPE)%

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
// %Tag(ACTION)%
    marker.action = visualization_msgs::Marker::ADD;

// %EndTag(ACTION)%

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
// %Tag(POSE)%
    marker.pose.position.x = pos;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = ori;
// %EndTag(POSE)%

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
// %Tag(SCALE)%
    marker.scale.x = threshold;
    marker.scale.y = threshold;
    marker.scale.z = threshold;
// %EndTag(SCALE)%

    // Set the color -- be sure to set alpha to something non-zero!
// %Tag(COLOR)%
    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = alpha;
// %EndTag(COLOR)%

// %Tag(LIFETIME)%
    marker.lifetime = ros::Duration();
// %EndTag(LIFETIME)%

    // Publish the marker
// %Tag(PUBLISH)%
   
  float pos_x = msg->pose.pose.position.x;
  float pos_y = msg->pose.pose.position.y;

  // give position tolerance of + or - the marker's radius
  bool atPickupZone = (pick_pos - threshold*5 < pos_x && pos_x < pick_pos + threshold*5);
  bool atDropoffZone = (drop_pos - threshold*5 < pos_x && pos_x < drop_pos + threshold*5);

  if (atPickupZone) {
    // pause 5s to simulate pickup
    ros::Duration(5).sleep();
    // hide marker and set it to new coordinates
    pos = drop_pos;
    ori = drop_ori;
    alpha = 0.0;
    marker.color.a = alpha;
    ROS_INFO("At pickup location...");
  } else if (atDropoffZone) {
    alpha = 1.0;
    marker.color.a = alpha;
    ROS_INFO("At dropoff location...");
  }
marker_pub.publish(marker);
  // publish marker
  //publishMarker();

}


// %Tag(INIT)%
int main( int argc, char** argv )
{
  
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  //ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber sub = n.subscribe("odom", 1000, odomCallback);
  //ros::Subscriber odom_sub = n.subscribe("/odom", 1000, odomCallback);
// %EndTag(INIT)%

  // Set our initial shape type to be a cube
// %Tag(SHAPE_INIT)%
  uint32_t shape = visualization_msgs::Marker::CUBE;
// %EndTag(SHAPE_INIT)%
  

// %Tag(MARKER_INIT)%
//  while (ros::ok())
//  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();
// %EndTag(MARKER_INIT)%

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
// %Tag(NS_ID)%
    marker.ns = "add_markers";
    marker.id = 0;
// %EndTag(NS_ID)%

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
// %Tag(TYPE)%
    marker.type = shape;
// %EndTag(TYPE)%

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
// %Tag(ACTION)%
    marker.action = visualization_msgs::Marker::ADD;

// %EndTag(ACTION)%

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
// %Tag(POSE)%
    marker.pose.position.x = pos;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = ori;
// %EndTag(POSE)%

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
// %Tag(SCALE)%
    marker.scale.x = threshold;
    marker.scale.y = threshold;
    marker.scale.z = threshold;
// %EndTag(SCALE)%

    // Set the color -- be sure to set alpha to something non-zero!
// %Tag(COLOR)%
    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = alpha;
// %EndTag(COLOR)%

// %Tag(LIFETIME)%
    marker.lifetime = ros::Duration();
// %EndTag(LIFETIME)%

    // Publish the marker
// %Tag(PUBLISH)%
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub.publish(marker);
// %EndTag(PUBLISH)%
	//ros::Duration(5.0).sleep();
    
        // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
// %Tag(POSE)%
	//pos = 0.0;
    //ori = 5.0;
// %EndTag(POSE)%

// %Tag(SLEEP_END)%
    //r.sleep();
//  }
// %EndTag(SLEEP_END)%

  ros::spin();
}
// %EndTag(FULLTEXT)%
