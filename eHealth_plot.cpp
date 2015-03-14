
#include "eHealth.h"
#include "arduPi.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>


#define COLOR_RESET "\x1b[0m"
#define COLOR_RED "\x1b[31m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_GREEN "\x1b[32m"

int prueba()
{
return 42;
}

int main (int argc, char **argv)
{
            if (argc != 2)  //It prints the menu
            {
                std::cout <<COLOR_CYAN<<"---- ---- ---- ---- \n Instructions: \n \n write: \t./eHealth_plot <sensor> \n \n ---- ---- ---- ---- \n Sensors:\n \n ECG \t \t // The electrocardiogram sensor \n Temperature \t // The body temperature \n GSR \t \t // The galvanic skin response \n ---- ---- ---- ----"<<COLOR_RESET<<std::endl;
            }

            else
            {
                unsigned long int time[1000], time_zero;
                float data[1000];

                struct timespec time_start, time_current[1000];
                int opt,i=0,duration,delay,delay_min;

                std::ofstream file_data;
                char path[30],input='Y';

                int (*sensor)();
                sensor = 0;

                if(argv[1]==std::string("ECG"))sensor = &prueba;//eHealth.getECG;
                else if(argv[1]== std::string("Temperature"))sensor = &prueba;//eHealth.getTemperature;
                else if(argv[1] == std::string("GSR"))
                {
                    do
                    {
                        std::cout<<COLOR_CYAN<<"Choose an option:\n[1] Conductance\n[2] Resistance\n[3] Conductance voltage"<<COLOR_RESET<< std::endl;
                        std::cin>>opt;
                        switch (opt)
                        {
                            case 1:
                                sensor = &eHealth.getSkinConductance; 
                                break;
                            case 2:
                                sensor = &eHealth.getSkinResistance;
                                break;
                            case 3:
                                sensor = &eHealth.getSkinConductanceVoltage; 
                                break;
                            default:
                                std::cout<<COLOR_BLUE<<"Wrong option, please choose one of the following:"<<COLOR_RESET<<std::endl;
                                break;

                        }
                    }while(sensor==0);

                }
                else
                {
                    std::cout <<COLOR_RED<<"ERROR: Wrong parameter. Run it without parameters to read the instructions."<<COLOR_RESET<<std::endl;
                    return (-1);
                }

                //It introduces the measurement settings
                std::cout<<COLOR_CYAN<<"\nIntroduce the minimum length of the measurament (in seconds)"<<COLOR_RESET<<std::endl;
                std::cin >> duration;
                do
                {
                    std::cout<<COLOR_CYAN<<"\nIntroduce the sample rate (in Hz, maximum 2500Hz)"<<COLOR_RESET<<std::endl;
                    std::cin>>delay;
                }while(delay<0||delay>2500);

                //duration = atoi(argv[1]);
                //if ((delay)>2500){std::cout <<"ERROR: 2500Hz is the maximum sample rate"<<'\n'; return (-1);}
                delay = 1000000/delay;
                if ((delay/1000)>duration) std::cout<<COLOR_BLUE<<"INFO: This could be up to " << delay/1000<< " seconds long."<<COLOR_RESET<<std::endl;
                else std::cout<<COLOR_BLUE<<"INFO: This could be up to " << delay/1000 + duration << " seconds long."<<COLOR_RESET<<std::endl;

                do
                {
                    std::cout<<COLOR_CYAN<<"\nIntroduce the name of the file where to save the data"<<COLOR_RESET<<std::endl;
                    std::cin>>path;

                    if(std::ifstream(path))
                    {   do
                        {
                            std::cout<<COLOR_BLUE<<"\nThe file already exists" <<COLOR_CYAN<<"\nDo you want to overwrite it? (Y/N) \n"<<COLOR_RESET;
                            std::cin >> input;
                            if ((input !='Y')&&(input != 'N'))std::cout<<COLOR_BLUE<<"\nPlease, tye Y or N"<<COLOR_RESET<<std::endl;
                        }while((input != 'Y')&&(input != 'N'));
                    }
                }while(input != 'Y');

                file_data.open(path);
                file_data<<'[';
                file_data.close();

                std::cout<<COLOR_CYAN<<"\nPress INTRO to start"<<COLOR_RESET<<std::endl;//No funciona.
                std::cin.ignore();
                std::cin.ignore();

                std::cout<<COLOR_BLUE<<"\nSetting measure time"<<COLOR_RESET<<std::endl;
                //It adjusts the time needed for each measure.
                for(i=0;i<100;i++)
                {
                    data[i]=(*sensor)();
                    clock_gettime(CLOCK_REALTIME,&time_current[i]);
                }
                for (i=0;i<100;i++)
                {
                 delay_min = delay_min + time_current[i].tv_nsec;
                }
                delay_min = delay_min/100000;

                std::cout<<COLOR_CYAN<<"Running. Please wait."<<COLOR_RESET<<std::endl;
                clock_gettime(CLOCK_REALTIME,&time_start);
                clock_gettime(CLOCK_REALTIME,&time_current[999]);
                time_zero = time_start.tv_sec*1000 + time_start.tv_nsec/1000000;

                while((time_current[999].tv_sec - time_start.tv_sec) <= duration)
                {
                    file_data.open(path,std::ofstream::app);

                    for(i=0;i<1000;i++)
                    {
                        data[i]= (*sensor)();//eHealth.getECG();
                        clock_gettime(CLOCK_REALTIME,&time_current[i]);
                        usleep(delay - delay_min); //Sleep in microseconds
                    }

                    for(i=0;i<1000;i++)
                    {
                        time[i]= (time_current[i].tv_sec*1000 + time_current[i].tv_nsec/1000000)-time_zero;
                        file_data << data[i] << ' ' << time[i] << ';'<<std::endl;
                    }

                    file_data.close();
                }

                file_data.open(path,std::ofstream::app);
                file_data<<']';
                file_data.close();
                std::cout<<COLOR_GREEN<<"Complete!"<<COLOR_RESET<<std::endl;
            }
return 0;
}


