#include "VisionProcessing.h"
#include <vector>
#include <string>
#include <iostream>
#include <chrono>


VisionProcessing::VisionProcessing() {
	// TODO Auto-generated constructor stub

}

VisionProcessing::~VisionProcessing() {
	// TODO Auto-generated destructor stub
}

void VisionProcessing::VisionThread() {
	int status = 1;
	int* status_ptr = &status;

	cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture(0);

int cWidth = 320;
	int cHeight = 240;
	int cExposure = 17;
	int cWhiteBalance = 5100;
  cs::UsbCamera camera = frc::CameraServer::GetInstance()->StartAutomaticCapture();

   camera.SetResolution(cWidth,cHeight);
	 camera.SetExposureManual(cExposure);
	 camera.SetWhiteBalanceManual(cWhiteBalance);

	cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo("USB Camera 0");


	cs::CvSource outputStreamStd = CameraServer::GetInstance()->PutVideo("Cam0", 320, 240);



	cv::Mat source;
	cv::Mat output;


	cv::Rect r1, r2;

	std::vector<std::vector<cv::Point> >* contours_ptr;
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Point> contour1;
	std::vector<cv::Point> contour2;


	while(true) {

	//	uint64_t grab_Frame_Status = -1;

		grab_Frame_Status = cvSink.GrabFrame(source);
//		std::cout << "Grab Frame Status: " << grab_Frame_Status << std::endl;

		//if (grab_Frame_Status == 0 && source.rows > 0) {
		if (source.rows > 0) {

			//usleep(0100000);

			GearPipeline.Process(source);

			contours_ptr = GearPipeline.GetFilterContoursOutput();
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
					int gear [2] = {(midpt_r1 [0] + midpt_r2 [0]) / 2, (midpt_r1 [1] + midpt_r2 [1]) / 2};

					cv::Point gear_midpoint( gear[0], gear[1]);
					cv::line(output, gear_midpoint, gear_midpoint, color, 4);

					Gear_x = gear[0];			// Transfer Gear Target x-location to other threads & Robot command functions
					e_Gear_x = Gear_x - 160;	// Define error in Gear_x location

		//			std::cout << "Midpoint of Rectangle 1: (" << midpt_r1 [0] << "," << midpt_r1 [1] << ")" << std::endl;
		//			std::cout << "Midpoint of Rectangle 2: (" << midpt_r2 [0] << "," << midpt_r2 [1] << ")" << std::endl;
		//			std::cout << "Gear Location: (" << gear [0] << "," << gear [1] << ")" << std::endl;
				} // if (size(contours) >= 2)
				else
				{
					e_Gear_x = 0;
				}

			} // if (!contours.empty())
			else
			{
				cv::Scalar color = cv::Scalar(180,105,255); // BGR for hot pink color

				cv::Point P1( 300, 220);
				cv::Point P2( 310, 230);
				cv::line(output, P1, P2, color, 4);
				e_Gear_x = 0;
			}
			outputStreamStd.PutFrame(output);
	//		usleep(0100000);
			}
	} // while(true)
}; //void Robot::VisionThread()

void VisionProcessing::VisionThreadBBoiler() {
	int status = 1;
	int* status_ptr = &status;

	cs::UsbCamera camera2 = CameraServer::GetInstance()->StartAutomaticCapture(1);
	camera2.SetResolution(320, 240);
	//camera2.SetExposureManual(50);
	//usleep(1000000);

	cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo("USB Camera 1");
	cs::CvSource outputStreamStd2 = CameraServer::GetInstance()->PutVideo("Cam1", 320, 240);

	cv::Mat source;
	cv::Mat output;

	grip::BBoilerPipeline BBoilerPipeline;

	cv::Rect r1, r8;

	std::vector<std::vector<cv::Point> >* contours_ptr;
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Point> contour1;
	std::vector<cv::Point> contour8;


	while(true) {

		cvSink.GrabFrame(source);

		BBoilerPipeline.Process(source);

		contours_ptr = BBoilerPipeline.GetFilterContoursOutput();
		contours = *contours_ptr;

//		cvtColor(source, output, cv::COLOR_BGR2RGB);
		output = source;

		cv::Scalar color2 = cv::Scalar(0,0,255); // BGR for red

		cv::Point r1tl = cv::Point(300, 220);
		cv::Point r1br = cv::Point(320, 240);
		cv::rectangle(output, r1tl, r1br, color2, 4, 8, 0);

		if (!contours.empty())
		{
			contour1 = contours[0];
			contour8 = contours[7];
			r1 = cv::boundingRect(contour1);
			r8 = cv::boundingRect(contour8);
			cv::Point tl1 = r1.tl();	//Rect_::x and Rect_::y
			cv::Point br1 = r1.br();
			cv::Point tl8 = r8.tl();	//Rect_::x and Rect_::y
			cv::Point br8 = r8.br();

			//cv::Scalar color2 = cv::Scalar(0,0,255); // BGR for red
//			cv::rectangle(output, tl1, br1, color2, 4, 8, 0);
//			cv::rectangle(output, tl8, br8, color2, 4, 8, 0);
			//cv::rectangle(source, r2.tl(), r2.br(), color, 4, 8, 0);

			int midpt_r1 [2] = {(tl1.x + br1.x) / 2, (tl1.y + br1.y) / 2};
			int midpt_r8 [2] = {(tl8.x + br8.x) / 2, (tl8.y + br8.y) / 2};
			int BBoiler [2] = {(midpt_r1 [0] + midpt_r8 [0]) / 2, (midpt_r1 [1] + midpt_r8 [1]) / 2};

			cv::Point BBoiler_midpoint(BBoiler[0], BBoiler[1]);
			cv::line(output, BBoiler_midpoint, BBoiler_midpoint, color2, 4);

			BBoiler_x = BBoiler[0];			// Transfer Gear Target x-location to other threads & Robot command functions
			e_BBoiler_x = BBoiler_x - 160;	// Define error in Gear_x location

//			std::cout << "Midpoint of Rectangle 1: (" << midpt_r1 [0] << "," << midpt_r1 [1] << ")" << std::endl;
//			std::cout << "Midpoint of Rectangle 2: (" << midpt_r2 [0] << "," << midpt_r2 [1] << ")" << std::endl;
//			std::cout << "Gear Location: (" << gear [0] << "," << gear [1] << ")" << std::endl;

		} // if (!contours.empty())
		outputStreamStd2.PutFrame(output);
	} // while(true)
}; //void Robot::VisionThread()

