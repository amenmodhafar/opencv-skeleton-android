#include <android/log.h>
#include <queue>
#include <opencv2/imgproc/imgproc.hpp>

#include "mainActivity.h"

#define  LOG_TAG    "native_activity"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

void processFrame(cv::Mat& mRgba){
	cv::Mat mGray, mGraySmall;
	cv::cvtColor(mRgba, mGray, CV_RGBA2GRAY);
	cv::Canny(mGray, mGray, 70, 200);

	cv::Mat mGray3Ch;
	cv::cvtColor(mGray, mRgba, CV_GRAY2RGBA);
}

float fps = 0;
std::queue<int64> time_queue;

void useFrame(cv::Mat& mRgba){

	int64 now = cv::getTickCount();
	int64 then;

	time_queue.push(now);

	// Process frame
	if(mRgba.cols != 0) {

		processFrame(mRgba);

		char buffer[256];
		sprintf(buffer, "Display performance: %dx%d @ %.3f", mRgba.cols, mRgba.rows, fps);
		cv::putText(mRgba, std::string(buffer), cv::Point(8,64),
				cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0,255,255,255));
	}

	if (time_queue.size() >= 2)
		then = time_queue.front();
	else
		then = 0;

	if (time_queue.size() >= 25)
		time_queue.pop();

	fps = time_queue.size() * (float)cv::getTickFrequency() / (now-then);
}

JNIEXPORT void JNICALL Java_com_jbboin_myopencvskeleton_CameraPreview_ImageProcessing(
		JNIEnv* env, jobject obj,
		jint width, jint height,
		jbyteArray NV21FrameData, jintArray outPixels){

	jbyte * pNV21FrameData = env->GetByteArrayElements(NV21FrameData, 0);
	jint * poutPixels = env->GetIntArrayElements(outPixels, 0);

	cv::Mat mYuv(height + height/2, width, CV_8UC1, (uchar*)pNV21FrameData);
	cv::Mat mRgba(height, width, CV_8UC4, (uchar *)poutPixels);
	cv::cvtColor(mYuv, mRgba, CV_YUV2BGRA_NV21);

	useFrame(mRgba);

	env->ReleaseByteArrayElements(NV21FrameData, pNV21FrameData, 0);
	env->ReleaseIntArrayElements(outPixels, poutPixels, 0);
}
