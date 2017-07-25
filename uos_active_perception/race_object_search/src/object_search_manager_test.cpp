#include "ros/ros.h"
#include "tf/tf.h"
#include "visualization_msgs/Marker.h"
#include "actionlib/client/simple_action_client.h"
#include "race_object_search/ObserveVolumesAction.h"
#include "uos_active_perception_msgs/ResetVolumes.h"

#include <cstring>
#include <cstdlib>

uos_active_perception_msgs::BoundingBox makeBox()
{
    uos_active_perception_msgs::BoundingBox box;
    box.pose_stamped.header.frame_id = "/map";
    box.pose_stamped.header.stamp = ros::Time::now();
    box.pose_stamped.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0,0,0);
    return box;
}

uos_active_perception_msgs::BoundingBox makeTable1()
{
    uos_active_perception_msgs::BoundingBox box = makeBox();
    box.pose_stamped.pose.position.x = 7.7;
    box.pose_stamped.pose.position.y = 11.5;
    box.pose_stamped.pose.position.z = 0.86;
    box.dimensions.x = .8;
    box.dimensions.y = .8;
    box.dimensions.z = .2;
    return box;
}

uos_active_perception_msgs::BoundingBox makeTable2()
{
    uos_active_perception_msgs::BoundingBox box = makeBox();
    box.pose_stamped.pose.position.x = 10.25;
    box.pose_stamped.pose.position.y = 11.5;
    box.pose_stamped.pose.position.z = 0.86;
    box.dimensions.x = .8;
    box.dimensions.y = .8;
    box.dimensions.z = .2;
    return box;
}

uos_active_perception_msgs::BoundingBox makeCounter()
{
    uos_active_perception_msgs::BoundingBox box = makeBox();
    box.pose_stamped.pose.position.x = 5.3;
    box.pose_stamped.pose.position.y = 10.08;
    box.pose_stamped.pose.position.z = 0.9;
    box.dimensions.x = 0.75;
    box.dimensions.y = 1.45;
    box.dimensions.z = 0.2;
    return box;
}

uos_active_perception_msgs::BoundingBox makeRaceRoom()
{
    uos_active_perception_msgs::BoundingBox box = makeBox();
    box.pose_stamped.pose.position.x = 8.8;
    box.pose_stamped.pose.position.y = 11.5;
    box.pose_stamped.pose.position.z =  1.0;
    box.dimensions.x = 10.0;
    box.dimensions.y = 5.0;
    box.dimensions.z = 2.0;
    return box;
}

uos_active_perception_msgs::BoundingBox makeShelf1()
{
    uos_active_perception_msgs::BoundingBox box = makeBox();
    box.pose_stamped.pose.position.x = 7.82;
    box.pose_stamped.pose.position.y = 9.25;
    box.pose_stamped.pose.position.z = 0.58;
    box.dimensions.x = 0.8;
    box.dimensions.y = 0.3;
    box.dimensions.z = 1.15;
    return box;
}

uos_active_perception_msgs::BoundingBox makeShelf2()
{
    uos_active_perception_msgs::BoundingBox box = makeBox();
    box.pose_stamped.pose.position.x = 3.3;
    box.pose_stamped.pose.position.y = 11.2;
    box.pose_stamped.pose.position.z = 0.58;
    box.dimensions.x = 0.3;
    box.dimensions.y = 2.7;
    box.dimensions.z = 1.15;
    return box;
}

uos_active_perception_msgs::BoundingBox makeShelf3()
{
    uos_active_perception_msgs::BoundingBox box = makeBox();
    box.pose_stamped.pose.position.x = -0.12;
    box.pose_stamped.pose.position.y = 11.2;
    box.pose_stamped.pose.position.z = 0.58;
    box.dimensions.x = 0.3;
    box.dimensions.y = 2.7;
    box.dimensions.z = 1.15;
    return box;
}

uos_active_perception_msgs::BoundingBox makeLuciaAreaE()
{
    uos_active_perception_msgs::BoundingBox box = makeBox();
    box.pose_stamped.pose.position.x = 5.2;
    box.pose_stamped.pose.position.y = 2.1;
    box.pose_stamped.pose.position.z = 0.275;
    box.dimensions.x = 1.0;
    box.dimensions.y = 1.6;
    box.dimensions.z = 0.55;
    return box;
}

uos_active_perception_msgs::BoundingBox makeLuciaAreaNW()
{
    uos_active_perception_msgs::BoundingBox box = makeBox();
    box.pose_stamped.pose.position.x = 2.3;
    box.pose_stamped.pose.position.y = 3.6;
    box.pose_stamped.pose.position.z = 0.275;
    box.dimensions.x = 1.8;
    box.dimensions.y = 1.0;
    box.dimensions.z = 0.55;
    return box;
}

uos_active_perception_msgs::BoundingBox makeLuciaAreaSW()
{
    uos_active_perception_msgs::BoundingBox box = makeBox();
    box.pose_stamped.pose.position.x = 1.9;
    box.pose_stamped.pose.position.y = 1.3;
    box.pose_stamped.pose.position.z = 0.275;
    box.dimensions.x = 1.8;
    box.dimensions.y = 1.0;
    box.dimensions.z = 0.55;
    return box;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "race_object_search_manager_test");
    ros::NodeHandle nh;
    ros::Publisher marker_pub = nh.advertise<visualization_msgs::Marker>("race_object_search_manager_test", 10);

    // Wait for subscribers to connect
    ros::WallDuration(1.0).sleep();

    // Create the request
    std::vector<uos_active_perception_msgs::BoundingBox> boxes;
    std::vector<double> probs;
    bool reset = false;
    bool clearall = false;
    bool nosearch = false;
    bool has_p = false;
    double min_p_succ = 0.0;

    for(long i = 1; i < argc; ++i) {
        if(!strcmp(argv[i], "reset")) {
            reset = true;
        } else if(!strcmp(argv[i], "clearall")) {
            clearall = true;
        } else if(!strcmp(argv[i], "nosearch")) {
            nosearch = true;
        } else if(!strcmp(argv[i], "p")) {
            has_p = true;
        } else if(!strcmp(argv[i], "min_p_succ")) {
            min_p_succ = std::atof(argv[++i]);
        } else if(!strcmp(argv[i], "table1")) {
            if(has_p) probs.push_back(std::atof(argv[++i]));
            boxes.push_back(makeTable1());
        } else if(!strcmp(argv[i], "table2")) {
            if(has_p) probs.push_back(std::atof(argv[++i]));
            boxes.push_back(makeTable2());
        } else if(!strcmp(argv[i], "counter")) {
            if(has_p) probs.push_back(std::atof(argv[++i]));
            boxes.push_back(makeCounter());
        } else if(!strcmp(argv[i], "raceRoom")) {
            if(has_p) probs.push_back(std::atof(argv[++i]));
            boxes.push_back(makeRaceRoom());
        } else if(!strcmp(argv[i], "shelf1")) {
            if(has_p) probs.push_back(std::atof(argv[++i]));
            boxes.push_back(makeShelf1());
        } else if(!strcmp(argv[i], "shelf2")) {
            if(has_p) probs.push_back(std::atof(argv[++i]));
            boxes.push_back(makeShelf2());
        } else if(!strcmp(argv[i], "shelf3")) {
            if(has_p) probs.push_back(std::atof(argv[++i]));
            boxes.push_back(makeShelf3());
        } else if(!strcmp(argv[i], "lucia_area_e")) {
            if(has_p) probs.push_back(std::atof(argv[++i]));
            boxes.push_back(makeLuciaAreaE());
        } else if(!strcmp(argv[i], "lucia_area_nw")) {
            if(has_p) probs.push_back(std::atof(argv[++i]));
            boxes.push_back(makeLuciaAreaNW());
        } else if(!strcmp(argv[i], "lucia_area_sw")) {
            if(has_p) probs.push_back(std::atof(argv[++i]));
            boxes.push_back(makeLuciaAreaSW());
        } else {
            ROS_ERROR_STREAM("UNKNOWN ARG: " << argv[i]);
        }
    }

    // Send a marker
    for(size_t i = 0; i < boxes.size(); ++i) {
        visualization_msgs::Marker marker;
        marker.action = visualization_msgs::Marker::ADD;
        marker.type = visualization_msgs::Marker::CUBE;
        marker.lifetime = ros::Duration();
        marker.scale.x = boxes[i].dimensions.x;
        marker.scale.y = boxes[i].dimensions.y;
        marker.scale.z = boxes[i].dimensions.z;
        marker.color.r = 1.0;
        marker.color.g = 1.0;
        marker.color.b = 0.0;
        marker.color.a = 0.5;
        marker.pose = boxes[i].pose_stamped.pose;
        marker.header = boxes[i].pose_stamped.header;
        marker.id = i;
        marker.ns = "observe_volumes";
        marker_pub.publish(marker);
    }

    // reset regions if commanded to
    if(reset || clearall) {
        ros::ServiceClient c = nh.serviceClient<uos_active_perception_msgs::ResetVolumes>("reset_volumes");
        uos_active_perception_msgs::ResetVolumes srv;
        srv.request.volumes.insert(srv.request.volumes.end(), boxes.begin(), boxes.end());
        srv.request.keep_occupied = !clearall;
        if(!c.exists()) {
            ROS_INFO("waiting for /reset_volumes");
            c.waitForExistence();
        }
        c.call(srv);
    }

    if(!nosearch) {
        actionlib::SimpleActionClient<race_object_search::ObserveVolumesAction> ac("observe_volumes", true);
        if(!ac.isServerConnected()) {
            ROS_INFO("waiting for /observe_volumes");
            ac.waitForServer();
        }
        race_object_search::ObserveVolumesGoal goal;
        goal.roi.insert(goal.roi.end(), boxes.begin(), boxes.end());
        // Set probabilities
        goal.p.resize(goal.roi.size());
        double total_volume = 0.0;
        for(size_t i = 0; i < goal.roi.size(); ++i) {
            total_volume += goal.roi[i].dimensions.x * goal.roi[i].dimensions.y * goal.roi[i].dimensions.z;
        }
        for(size_t i = 0; i < goal.roi.size(); ++i) {
            if(has_p) {
                goal.p[i] = probs[i];
            } else {
                goal.p[i] = (goal.roi[i].dimensions.x * goal.roi[i].dimensions.y * goal.roi[i].dimensions.z) / total_volume;
            }
        }
        goal.min_p_succ = min_p_succ;
        ROS_INFO("Sending goal...");
        ac.sendGoal(goal);
        ac.waitForResult();
        if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        {
            ROS_INFO("... completed!");
        }
        else
        {
            ROS_ERROR("... failed!");
        }
    }

    ros::spinOnce();
}

