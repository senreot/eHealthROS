
#include "ros/ros.h"
#include "prueba/eHealth_param.h"

#include <sstream>

#include <stdio.h>
#include <sys/time.h>

#include "eHealth.h"
#include "arduPi.h"


/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line. For programmatic
   * remappings you can use a different version of init() which takes remappings
   * directly, but for most command-line programs, passing argc and argv is the easiest
   * way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "test_tiempos");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;

  /**
   * The advertise() function is how you tell ROS that you want to
   * publish on a given topic name. This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing. After this advertise() call is made, the master
   * node will notify anyone who is trying to subscribe to this topic name,
   * and they will in turn negotiate a peer-to-peer connection with this
   * node.  advertise() returns a Publisher object which allows you to
   * publish messages on that topic through a call to publish().  Once
   * all copies of the returned Publisher object are destroyed, the topic
   * will be automatically unadvertised.
   *
   * The second parameter to advertise() is the size of the message queue
   * used for publishing messages.  If messages are published more quickly
   * than we can send them, the number here specifies how many messages to
   * buffer up before throwing some away.
   */
  ros::Publisher chatter_pub = n.advertise<prueba::eHealth_param>("tiempos", 1000);

  ros::Rate loop_rate(10);

    prueba::eHealth_param parametros;

    struct timeval comienzo, final;

//Pulsioximeter
gettimeofday(&comienzo,NULL);
eHealth.initPulsioximeter();
gettimeofday(&final,NULL);
ROS_INFO("La funcion initPulsioximeter() [init %d - end %d] \n ha tardado %d microsegundos\n", (final.tv_sec*1000000+final.tv_usec),
(comienzo.tv_sec*1000000+comienzo.tv_usec),(final.tv_sec*1000000+final.tv_usec-comienzo.tv_sec*1000000-comienzo.tv_usec));


gettimeofday(&comienzo,NULL);
eHealth.readPulsioximeter();
gettimeofday(&final,NULL);
ROS_INFO("La funcion readPulsioximeter() [init %d - end %d] \n ha tardado %d microsegundos\n", (final.tv_sec*1000000+final.tv_usec),(comienzo.tv_sec*1000000+comienzo.tv_usec),(final.tv_sec*1000000+final.tv_usec-comienzo.tv_sec*1000000-comienzo.tv_usec));


gettimeofday(&comienzo,NULL);
parametros.BPM = eHealth.getBPM();
gettimeofday(&final,NULL);
ROS_INFO("La funcion getBPM() [init %d - end %d] \n ha tardado %d microsegundos\n", (final.tv_sec*1000000+final.tv_usec),(comienzo.tv_sec*1000000+comienzo.tv_usec),(final.tv_sec*1000000+final.tv_usec-comienzo.tv_sec*1000000-comienzo.tv_usec));


gettimeofday(&comienzo,NULL);
parametros.SPO2 = eHealth.getOxygenSaturation();
gettimeofday(&final,NULL);
ROS_INFO("La funcion getOxygenSaturation() [init %d - end %d] \n ha tardado %d microsegundos\n", (final.tv_sec*1000000+final.tv_usec),(comienzo.tv_sec*1000000+comienzo.tv_usec),(final.tv_sec*1000000+final.tv_usec-comienzo.tv_sec*1000000-comienzo.tv_usec));


//Electrocardiogram
gettimeofday(&comienzo,NULL);
parametros.ECGvolt = eHealth.getECG();
gettimeofday(&final,NULL);
ROS_INFO("La funcion getECG() [init %d - end %d] \n ha tardado %d microsegundos\n", (final.tv_sec*1000000+final.tv_usec),(comienzo.tv_sec*1000000+comienzo.tv_usec),(final.tv_sec*1000000+final.tv_usec-comienzo.tv_sec*1000000-comienzo.tv_usec));


//Electromyogram
gettimeofday(&comienzo,NULL);
parametros.EMG = eHealth.getEMG();
gettimeofday(&final,NULL);
ROS_INFO("La funcion getEMG() [init %d - end %d] \n ha tardado %d microsegundos\n", (final.tv_sec*1000000+final.tv_usec),(comienzo.tv_sec*1000000+comienzo.tv_usec),(final.tv_sec*1000000+final.tv_usec-comienzo.tv_sec*1000000-comienzo.tv_usec));


//AirFlow
gettimeofday(&comienzo,NULL);
parametros.airFlow =eHealth.getAirFlow();
gettimeofday(&final,NULL);
ROS_INFO("La funcion getAirFlow() [init %d - end %d] \n ha tardado %d microsegundos\n", (final.tv_sec*1000000+final.tv_usec),(comienzo.tv_sec*1000000+comienzo.tv_usec),(final.tv_sec*1000000+final.tv_usec-comienzo.tv_sec*1000000-comienzo.tv_usec));


gettimeofday(&comienzo,NULL);
eHealth.airFlowWave(parametros.airFlow);
gettimeofday(&final,NULL);
ROS_INFO("La funcion airFlowWave() [init %d - end %d] \n ha tardado %d microsegundos\n", (final.tv_sec*1000000+final.tv_usec),(comienzo.tv_sec*1000000+comienzo.tv_usec),(final.tv_sec*1000000+final.tv_usec-comienzo.tv_sec*1000000-comienzo.tv_usec));


//Body temperature
gettimeofday(&comienzo,NULL);
parametros.temperature =eHealth.getTemperature();
gettimeofday(&final,NULL);
ROS_INFO("La funcion getTemperature() [init %d - end %d] \n ha tardado %d microsegundos\n", (final.tv_sec*1000000+final.tv_usec),(comienzo.tv_sec*1000000+comienzo.tv_usec),(final.tv_sec*1000000+final.tv_usec-comienzo.tv_sec*1000000-comienzo.tv_usec));


//Blood pressure
gettimeofday(&comienzo,NULL);
eHealth.readBloodPressureSensor();
gettimeofday(&final,NULL);
ROS_INFO("La funcion readBloodPressureSensor() [init %d - end %d] \n ha tardado %d microsegundos\n", (final.tv_sec*1000000+final.tv_usec),(comienzo.tv_sec*1000000+comienzo.tv_usec),(final.tv_sec*1000000+final.tv_usec-comienzo.tv_sec*1000000-comienzo.tv_usec));


gettimeofday(&comienzo,NULL);
parametros.numberOfData = eHealth.getBloodPressureLength();
gettimeofday(&final,NULL);
ROS_INFO("La funcion getBlodPressureSensor() [init %d - end %d] \n ha tardado %d microsegundos\n", (final.tv_sec*1000000+final.tv_usec),(comienzo.tv_sec*1000000+comienzo.tv_usec),(final.tv_sec*1000000+final.tv_usec-comienzo.tv_sec*1000000-comienzo.tv_usec));

/** 
gettimeofday(&comienzo,NULL);
for (int i=0;i<parametros.numberOfData;i++) parametros.systolic = eHealth.bloodPressureDataVector[i].systolic;
gettimeofday(&final,NULL);
ROS_INFO("La funcion bloodPressureDataVector[i].systolic() [init %d - end %d] \n ha tardado %d microsegundos\n", (final.tv_sec*1000000+final.tv_usec),(comienzo.tv_sec*1000000+comienzo.tv_usec),(final.tv_sec*1000000+final.tv_usec-comienzo.tv_sec*1000000-comienzo.tv_usec));


gettimeofday(&comienzo,NULL);
for (i=0;i<parametros.numberOfData;i++) parametros.diastolic =eHealth.getDiastolicPressure();
gettimeofday(&final,NULL);
ROS_INFO("La funcion getDiastolicPressure() [init %d - end %d] \n ha tardado %d microsegundos\n", (final.tv_sec*1000000+final.tv_usec),(comienzo.tv_sec*1000000+comienzo.tv_usec),(final.tv_sec*1000000+final.tv_usec-comienzo.tv_sec*1000000-comienzo.tv_usec));
**/

//Body position
gettimeofday(&comienzo,NULL);
eHealth.initPositionSensor();
gettimeofday(&final,NULL);
ROS_INFO("La funcion initPositionSensor() [init %d - end %d] \n ha tardado %d microsegundos\n", (final.tv_sec*1000000+final.tv_usec),(comienzo.tv_sec*1000000+comienzo.tv_usec),(final.tv_sec*1000000+final.tv_usec-comienzo.tv_sec*1000000-comienzo.tv_usec));


gettimeofday(&comienzo,NULL);
parametros.position = eHealth.getBodyPosition();
gettimeofday(&final,NULL);
ROS_INFO("La funcion getBodyPosition() [init %d - end %d] \n ha tardado %d microsegundos\n", (final.tv_sec*1000000+final.tv_usec),(comienzo.tv_sec*1000000+comienzo.tv_usec),(final.tv_sec*1000000+final.tv_usec-comienzo.tv_sec*1000000-comienzo.tv_usec));


gettimeofday(&comienzo,NULL);
eHealth.printPosition(parametros.position);
gettimeofday(&final,NULL);
ROS_INFO("La funcion printPosition(parametros.position) [init %d - end %d] \n ha tardado %d microsegundos\n", (final.tv_sec*1000000+final.tv_usec),(comienzo.tv_sec*1000000+comienzo.tv_usec),(final.tv_sec*1000000+final.tv_usec-comienzo.tv_sec*1000000-comienzo.tv_usec));


//Galvanic skin response
gettimeofday(&comienzo,NULL);
parametros.conductance = eHealth.getSkinConductance();
gettimeofday(&final,NULL);
ROS_INFO("La funcion getSkinConductance() [init %d - end %d] \n ha tardado %d microsegundos\n", (final.tv_sec*1000000+final.tv_usec),(comienzo.tv_sec*1000000+comienzo.tv_usec),(final.tv_sec*1000000+final.tv_usec-comienzo.tv_sec*1000000-comienzo.tv_usec));


gettimeofday(&comienzo,NULL);
parametros.resistance = eHealth.getSkinResistance();
gettimeofday(&final,NULL);
ROS_INFO("La funcion getSkinResistance() [init %d - end %d] \n ha tardado %d microsegundos\n", (final.tv_sec*1000000+final.tv_usec),(comienzo.tv_sec*1000000+comienzo.tv_usec),(final.tv_sec*1000000+final.tv_usec-comienzo.tv_sec*1000000-comienzo.tv_usec));


gettimeofday(&comienzo,NULL);
parametros.conductanceVol = eHealth.getSkinConductanceVoltage();
gettimeofday(&final,NULL);
ROS_INFO("La funcion getSkinConductanceVol() [init %d - end %d] \n ha tardado %d microsegundos\n", (final.tv_sec*1000000+final.tv_usec),(comienzo.tv_sec*1000000+comienzo.tv_usec),(final.tv_sec*1000000+final.tv_usec-comienzo.tv_sec*1000000-comienzo.tv_usec));


//Glucometer
gettimeofday(&comienzo,NULL);
eHealth.readGlucometer();
gettimeofday(&final,NULL);
ROS_INFO("La funcion readGlucometer() [init %d - end %d] \n ha tardado %d microsegundos\n", (final.tv_sec*1000000+final.tv_usec),(comienzo.tv_sec*1000000+comienzo.tv_usec),(final.tv_sec*1000000+final.tv_usec-comienzo.tv_sec*1000000-comienzo.tv_usec));


gettimeofday(&comienzo,NULL);
parametros.glucose = eHealth.getGlucometerLength();
gettimeofday(&final,NULL);
ROS_INFO("La funcion getGlucometerLength() [init %d - end %d] \n ha tardado %d microsegundos\n", (final.tv_sec*1000000+final.tv_usec),(comienzo.tv_sec*1000000+comienzo.tv_usec),(final.tv_sec*1000000+final.tv_usec-comienzo.tv_sec*1000000-comienzo.tv_usec));
 





    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
    chatter_pub.publish(parametros);

    ros::spinOnce();


    loop_rate.sleep();


  return 0;
}
