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
    
	gCamera.open(_camera_id.get());			// Openning camera device

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

    base::samples::frame::Frame rockFrame;								// Rock's frame format
	cv::Mat openCVFrame;												// OpenCV's frame format
	gCamera >> openCVFrame;												// Getting the frame in the OpenCV's format
	frame_helper::FrameHelper::copyMatToFrame(openCVFrame, rockFrame); 	// Converting OpenCV's frame format into rock's frame format
	_frame.write(rockFrame);
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

