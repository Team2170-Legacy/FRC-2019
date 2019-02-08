#include "VisionProcessing.h"
//#include "GripPipeline.cpp"  BAD
#include "GripPipeline.h"
#include <vector>
#include <string>
#include <iostream>
#include <chrono>



VisionProcessing::VisionProcessing() {
	// TODO Auto-generated constructor stub

}

//VisionProcessing::~VisionProcessing() {
	// TODO Auto-generated destructor stub
//}

void VisionProcessing::VisionThread() {
grip::GripPipeline pipeline;


	cs::UsbCamera camera = frc::CameraServer::GetInstance()->StartAutomaticCapture(0);

int cWidth = 320;
	int cHeight = 240;
	int cExposure = 17;
	int cWhiteBalance = 5100;
  //cs::UsbCamera camera = frc::CameraServer::GetInstance()->StartAutomaticCapture();

   camera.SetResolution(cWidth,cHeight);
	 camera.SetExposureManual(cExposure);
	 camera.SetWhiteBalanceManual(cWhiteBalance);

	cs::CvSink cvSink = frc::CameraServer::GetInstance()->GetVideo("USB Camera 0");


	cs::CvSource outputStreamStd = frc::CameraServer::GetInstance()->PutVideo("Cam0", 320, 240);



	cv::Mat source;
	cv::Mat output;


	cv::Rect r1, r2;

	std::vector<std::vector<cv::Point> >* contours_ptr;
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Point> contour1;
	std::vector<cv::Point> contour2;


	while(true) {

	//	uint64_t grab_Frame_Status = -1;

		cvSink.GrabFrame(source);
//		std::cout << "Grab Frame Status: " << grab_Frame_Status << std::endl;

		//if (grab_Frame_Status == 0 && source.rows > 0) {
		if (source.rows > 0) {

			//usleep(0100000);

			pipeline.Process(source);

			contours_ptr = pipeline.GetFilterContoursOutput();
			contours = *contours_ptr;

	//		cvtColor(source, output, cv::COLOR_BGR2RGB);
			output = source;

			if (!contours.empty())
	//		if (false)
			{
				if (contours.size() >= 2)
				{
					contour1 = contours[0];
					contour2 = contours[1];
					r1 = cv::boundingRect(contour1);
					r2 = cv::boundingRect(contour2);
					cv::Point tl1 = r1.tl();	//Rect_::x and Rect_::y
					cv::Point br1 = r1.br();
					cv::Point tl2 = r2.tl();	//Rect_::x and Rect_::y
					cv::Point br2 = r2.br();

					cv::Scalar color = cv::Scalar(180,105,255); // BGR for hot pink color
					cv::rectangle(output, tl1, br1, color, 4, 8, 0);
					cv::rectangle(output, tl2, br2, color, 4, 8, 0);

					int midpt_r1 [2] = {(tl1.x + br1.x) / 2, (tl1.y + br1.y) / 2};
					int midpt_r2 [2] = {(tl2.x + br2.x) / 2, (tl2.y + br2.y) / 2};
					int target[2] = {(midpt_r1 [0] + midpt_r2 [0]) / 2, (midpt_r1 [1] + midpt_r2 [1]) / 2};

					cv::Point target_midpoint( target[0], target[1]);
					cv::line(output, target_midpoint, target_midpoint, color, 4);

					Target_x = target[0];			// Transfer Target x-location to other threads & Robot command functions
					e_Target_x = Target_x - 160;	// Define error in Target_x location

		//			std::cout << "Midpoint of Rectangle 1: (" << midpt_r1 [0] << "," << midpt_r1 [1] << ")" << std::endl;
		//			std::cout << "Midpoint of Rectangle 2: (" << midpt_r2 [0] << "," << midpt_r2 [1] << ")" << std::endl;
		//			std::cout << "Target Location: (" << target [0] << "," << target [1] << ")" << std::endl;
				} 
				else
				{
					e_Target_x = 0;
				}

			} // if (!contours.empty())
			else
			{
				cv::Scalar color = cv::Scalar(180,105,255); // BGR for hot pink color

				cv::Point P1( 300, 220);
				cv::Point P2( 310, 230);
				cv::line(output, P1, P2, color, 4);
				e_Target_x = 0;
			}
			outputStreamStd.PutFrame(output);
	
			}
	} 
}

