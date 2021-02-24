#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"
#include<random>
#include <sstream>
#include "std_msgs/Float32.h"
   
   class poisson_sub{
   private:
   ros:: Subrscriber s;
   ros:: Publicsher p;
   public: 
   poisson_sub(ros::NodeHandle *n){
   publish = n->advertise<std_msgs::Float32MultiArray>("/min_distance", 1000);
   
   subscribe = n->subscriber("/random_generator", 1000, this);
  }

   
void minCallback(const std_msgs::Float32MultiArray& msg){
	
	int height = msg->layout.dim[0].size;
	std_msgs::Float32 minimum;

	for(int i = 0; i < height; i++){
	    if(msg->data[i] < minimum.data){
		minimum.data = msg->data[i];
		}
	}
			
		ros::Rate loop_rate(10);
		while(ros::ok()){
		p.publish(minimum);
		loop_rate.sleep();
		ros::spinOnce();
		}
	

	}
};

   
  
   int main(int argc, char **argv)
   {

     ros::init(argc, argv, "min_distance"); 
     ros::NodeHandle n;
     poisson_sub sub = poisson_sub(&n);
     ros::spin();
   
    return 0;
  }
  
  
  

