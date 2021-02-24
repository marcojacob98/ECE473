   #include "ros/ros.h "
   #include "std_msgs/Float32MultiArray.h"
   #include<random>
   #include <sstream>
   using namespace std;
   
   
   
class poisson_pub{
    private:
    ros::Publisher p;
    public
    poisson_pub(ros::NodeHandle n){
    p = n.advertise<std_msgs::Float32MultiArray>("/random_generator", 1000);
  }

    
void getData(){
	int data[180];
	int num[180];
	int count = 0;

	std::random_device ran;
	std::mt19937 generate(ran());
	std::poisson_distribution<int> distribution;
	std_msgs::Float32MultiArray Points;
		

	
	for(int i = 0; i < sizeof(num)/4;i++){
		num[i] = distribution(generate);
		count++;
	}	
	for(int j = 0; j < sizeof(data)/4; j++){
		data[j] = (num[j]*80)/(*std::max_element(num, num + count));
		}	
	for(int k = 0; k < sizeof(data)/4; k++){
			Points.data.push_back((float) data[k]);
		}
		
		
	p.publish(Points);
		
	}
        
        

   }

};

int main(int argc, char **argv){
   
	
	ros::init(argc, argv, "poisson_distribution");
	ros::NodeHandle n;	 
	ros::Rate loop_rate(10);
	
	while(ros::ok()){	
	poisson_pub pub = poisson_pub(n);
	pub.generatePoissonData();
	loop_rate.sleep();
	}
	
  
  
    return 0;
 }
  
  

