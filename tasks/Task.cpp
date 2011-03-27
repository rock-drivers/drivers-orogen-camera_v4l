/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"

using namespace camera_v4l;

Task::Task(std::string const& name)
    : TaskBase(name)
{
}

Task::~Task()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Task.hpp for more detailed
// documentation about them.

bool Task::configureHook()
{
    if (! TaskBase::configureHook())
        return false;
    capture = cvCreateCameraCapture(0);
    if(!capture){
	fprintf(stderr,"Cannot open captureing device\n");
	return false;    
    }
    frame = cvQueryFrame(capture);
    base::samples::frame::Frame *base_frame = new base::samples::frame::Frame;
    
    base_frame->init(frame->width,frame->height,8,base::samples::frame::MODE_RGB);    
    camera_frame.reset(base_frame);
    return true;
}
// bool Task::startHook()
// {
//     if (! TaskBase::startHook())
//         return false;
//     return true;
// }
void Task::updateHook()
{
    TaskBase::updateHook();
    frame = cvQueryFrame(capture);
    base::samples::frame::Frame *frame_ptr = camera_frame.write_access();
    frame_ptr->setImage((char*)frame->imageData, sizeof(char) * frame->width * frame->height * 3);
    camera_frame.reset(frame_ptr);
    _frame.write(camera_frame);
}
// void Task::errorHook()
// {
//     TaskBase::errorHook();
// }
// void Task::stopHook()
// {
//     TaskBase::stopHook();
// }
// void Task::cleanupHook()
// {
//     TaskBase::cleanupHook();
// }

