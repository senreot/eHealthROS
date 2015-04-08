
#include "ros/ros.h"
#include "std_msgs/Int32.h"

#include <time.h>
#include <unistd.h>
#include <iostream>

#include "eHealth.h"
#include "arduPi.h"


/**
 * This program publish the beats per minute in a ROS topic
 */
int main(int argc, char **argv)
{
    unsigned long int time[10000], time_zero;
    int i, delay_min,delay, data_length=10001;
    float data[10000];
    struct timespec time_start, time_current[10000];

    ros::init(argc, argv, "beats_per_minute");
    ros::NodeHandle n;



    do
    {
        std::cout<<"Sample rate in Hz? (max. 2500)\n";
        std::cin>>delay;

        std::cout<<"refresh length in seconds?\n";
        std::cin>>data_length;
        std::cout<<"Running!\n";

        data_length = data_length*delay;
        if(data_length>=10000) std::cout<<"The sample rate or the refresh lentgh is to high, please reduce someone.\n";

    }while(data_length>=10000);

    delay=1000000/delay;

    ros::Publisher beats_pub = n.advertise<std_msgs::Int32>("beats_per_minute", 1000);
    //ros::Rate loop_rate(500);

    std_msgs::Int32 beats;


    while (ros::ok())
    {
        delay_min=0;
        for(i=0;i<100;i++)
        {
            data[i]=eHealth.getECG();
            clock_gettime(CLOCK_REALTIME,&time_current[i]);
        }
        for (i=0;i<99;i++)
        {
            delay_min = delay_min + time_current[i+1].tv_nsec - time_current[i].tv_nsec;
        }
        delay_min = delay_min/99000;

        clock_gettime(CLOCK_REALTIME,&time_start);
        clock_gettime(CLOCK_REALTIME,&time_current[(data_length-1)]);
        time_zero = time_start.tv_sec*1000 + time_start.tv_nsec/1000000;

        for(i=0;i<data_length;i++)
        {
            data[i]=eHealth.getECG();
            clock_gettime(CLOCK_REALTIME,&time_current[i]);
            //std::cout<<time_current[i].tv_sec<<'\n';
            usleep(delay - delay_min); //Sleep in microseconds
        }


        beats.data = 42;

        //ROS_INFO("%d", beats.data);
        beats_pub.publish(beats);
        ros::spinOnce();
        //loop_rate.sleep();
        }


    return 0;
}
