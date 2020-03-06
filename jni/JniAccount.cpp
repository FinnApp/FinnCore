#include <jni.h>

#include "Account.hpp"

extern "C" JNIEXPORT jint JNICALL Java_Account_getCount(JNIEnv* /*env*/, jobject /*obj*/)
{
    return Account::getCount();
}
