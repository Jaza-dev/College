#include "UI_XYGraph.h"

JNIEXPORT jdouble JNICALL Java_UI_XYGraph_calculateSizeOfPointY
(JNIEnv*, jobject, jdouble Yoffset , jint offsetValue) {
	return Yoffset / offsetValue;
}