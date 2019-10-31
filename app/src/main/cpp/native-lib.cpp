#include <jni.h>
#include <android/log.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define TAG "NativeLib"

using namespace std;
using namespace cv;

extern "C" {
void JNICALL
/*Java_com_example_nativeopencvandroidtemplate_MainActivity_adaptiveThresholdFromJNI(JNIEnv *env,
                                                                                   jobject instance,
                                                                                   jlong matAddr) {
*/
Java_com_example_nativeopencvandroidtemplate_MainActivity_adaptiveThresholdFromJNI(JNIEnv *env,
                                                                                   jobject instance,
                                                                                   jlong matAddr_input_rgba,
                                                                                   jlong matAddr_output_gray) {

    // get Mat from raw address
    //Mat &mat = *(Mat *) matAddr;
    Mat &mat_input_rgba = *(Mat *) matAddr_input_rgba, &mat_output_gray = *(Mat *) matAddr_output_gray;

    clock_t begin = clock();

    //adaptiveThreshold(mat, mat, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 21, 5);
    Mat mat_input_gray; cvtColor(mat_input_rgba, mat_input_gray, COLOR_RGBA2GRAY);
    adaptiveThreshold(mat_input_gray, mat_output_gray, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 21, 5);

    // log computation time to Android Logcat
    double totalTime = double(clock() - begin) / CLOCKS_PER_SEC;
    __android_log_print(ANDROID_LOG_INFO, TAG, "adaptiveThreshold computation time = %f seconds\n",
                        totalTime);
}
}