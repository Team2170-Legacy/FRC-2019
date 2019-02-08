/*
 * VisionProcessing.h
 *
 */

#ifndef SRC_VISION_VISIONPROCESSING_H_
#define SRC_VISION_VISIONPROCESSING_H_
#include "frc/WPILib.h"
#include "GripPipeline.h"




class VisionProcessing {
private:
	static void VisionThreadBBoiler();

public:
	VisionProcessing();
	static void VisionThread();
	virtual ~VisionProcessing();

	
	grip::GripPipeline pipeline;
	static int Target_x;			// Global Gear Target x-location (in 320x240 image coordinates)
	static int e_Target_x;		// Global variable for error in Gear_x location

	
};

#endif /* SRC_VISION_VISIONPROCESSING_H_ */
