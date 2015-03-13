
#include "eHealth.h"
#include "arduPi.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int main (int argc, char **argv)
{
            unsigned long int time[1000], time_zero;
            float data[1000];
            struct timespec time_start, time_current[1000];
            int i,duration,delay;
            std::ofstream file_data;


            if (argc != 4)
            {
                std::cout <<"Using this program:"<<'\n'<<"./ECG_plot <minimum_duration(seconds)> <sample_rate(Hz)> <file generated>"<<'\n';
            }

            else
            {

                duration = atoi(argv[1]);
                if ((delay=atoi(argv[2]))>2500){std::cout <<"ERROR: 2500Hz is the maximum sample rate"<<'\n'; return (-1);}
                delay = 1000000/delay;
                if ((delay/1000)>duration) std::cout<<"This could be up to " << delay/1000<< " seconds long."<<'\n';
                else std::cout<<"This could be up to " << delay/1000 + duration << " seconds long."<<'\n';

                file_data.open(argv[3]);
                file_data<<'[';
                file_data.close();

                clock_gettime(CLOCK_REALTIME,&time_start);
                clock_gettime(CLOCK_REALTIME,&time_current[999]);
                time_zero = time_start.tv_sec*1000 + time_start.tv_nsec/1000000;

                while((time_current[999].tv_sec - time_start.tv_sec) <= duration)
                {
                    file_data.open(argv[3],std::ofstream::app);

                    for(i=0;i<1000;i++)
                    {
                        data[i]= eHealth.getECG();
                        clock_gettime(CLOCK_REALTIME,&time_current[i]);
                        usleep(delay - 400); //Sleep in microseconds
                    }

                    for(i=0;i<1000;i++)
                    {
                        time[i]= (time_current[i].tv_sec*1000 + time_current[i].tv_nsec/1000000)-time_zero;
                        file_data << data[i] << ' ' << time[i] << ';'<<'\n';
                    }

                    file_data.close();
                }

                file_data.open(argv[3],std::ofstream::app);
                file_data<<']';
                file_data.close();
            }
return 0;
}


