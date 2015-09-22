#include <stdio.h>
#include <stdlib.h>
#include "cn_chaitin_sqlchop_SQLChop.h"
#include "sqlchop.h"

#define MAX_BUF_LEN 0x1000

struct sqlchop_object_t *get_sqlchop_object(JNIEnv *env, jobject obj) {
    jclass cls;
    jfieldID fid;
    if (obj == NULL) {
        return NULL;
    }
    cls = (*env)->GetObjectClass(env, obj);
    fid = (*env)->GetFieldID(env, cls, "sqlchop", "J");
    if (fid == NULL) {
        return NULL;
    }
    return *(struct sqlchop_object_t **)(*env)->GetLongField(env, obj, fid);
}

jboolean set_sqlchop_object(JNIEnv *env, jobject obj, jlong value) {
    jclass cls;
    jfieldID fid;
    if (obj == NULL) {
        return JNI_FALSE;
    }
    cls = (*env)->GetObjectClass(env, obj);
    fid = (*env)->GetFieldID(env, cls, "sqlchop", "J");
    if (fid == NULL) {
        return JNI_FALSE;
    }
    (*env)->SetLongField(env, obj, fid, value);
    return JNI_TRUE;
}

JNIEXPORT jint JNICALL Java_cn_chaitin_sqlchop_SQLChop_init(JNIEnv *env, jobject obj) {
    int ret;
    struct sqlchop_object_t **sqlchop;

    sqlchop = (struct sqlchop_object_t **)malloc(sizeof(struct sqlchop_object_t **));
    ret = sqlchop_init(NULL, sqlchop);

    set_sqlchop_object(env, obj, (jlong)sqlchop);
    
    return ret;
}

JNIEXPORT void JNICALL Java_cn_chaitin_sqlchop_SQLChop_release(JNIEnv *env, jobject obj) {
    struct sqlchop_object_t *sqlchop;

    sqlchop = get_sqlchop_object(env, obj);

    if (sqlchop) { 
        sqlchop_release(sqlchop);
        free(sqlchop);
    }
}

JNIEXPORT jfloat JNICALL Java_cn_chaitin_sqlchop_SQLChop_score_1sqli(JNIEnv *env, jobject obj, jstring payload) {
    const struct sqlchop_object_t *sqlchop;
    jfloat ret;

    ret = 0;

    if (payload != NULL) {
        sqlchop = get_sqlchop_object(env, obj);
        if (sqlchop) { 
            jsize len;
            const char *buf;
            len = (*env)->GetStringLength(env, payload);
            buf = (*env)->GetStringUTFChars(env, payload, JNI_FALSE);
            if (buf) {
                ret = sqlchop_score_sqli(sqlchop, buf, len);
                (*env)->ReleaseStringUTFChars(env, payload, buf);
            }
        }
    }
    return ret;
}

JNIEXPORT jint JNICALL Java_cn_chaitin_sqlchop_SQLChop_classify_1request(JNIEnv *env, jobject obj, jobjectArray buf, jboolean detail) {
    const struct sqlchop_object_t *sqlchop;
    int ret;
    jobjectArray buf_req, buf_rsp;
    jbyte *jbyte_buf_req;
    jsize len_buf_req;
    jbyte jbyte_buf_rsp[MAX_BUF_LEN];
    jlong len_buf_rsp;
     
    ret = 0;

    if (buf == NULL) {
        return ret;
    }
    if ((*env)->GetArrayLength(env, buf) != 2) {
        return ret;
    }

    buf_req = (jobjectArray)(*env)->GetObjectArrayElement(env, buf, 0);
    if (buf_req == NULL) {
        return ret;
    }

    sqlchop = get_sqlchop_object(env, obj);
    len_buf_req = (*env)->GetArrayLength(env, buf_req);
    jbyte_buf_req = (jbyte*)malloc(len_buf_req);

    if (jbyte_buf_req == NULL) {
        return ret;
    }

    (*env)->GetByteArrayRegion(env, buf_req, 0, len_buf_req, jbyte_buf_req);

    if (detail) {
        ret = sqlchop_classify_request(sqlchop, (const char*)jbyte_buf_req, len_buf_req, (char*)jbyte_buf_rsp, MAX_BUF_LEN, (unsigned long*)&len_buf_rsp, 1);

        buf_rsp = (*env)->NewByteArray(env, len_buf_rsp);
        if (buf_rsp) {
            (*env)->SetByteArrayRegion(env, buf_rsp, 0, len_buf_rsp, (const jbyte *)jbyte_buf_rsp);
            (*env)->SetObjectArrayElement(env, buf, 1, buf_rsp);
        }
    } else {
        ret = sqlchop_classify_request(sqlchop, (const char*)jbyte_buf_req, len_buf_req, NULL, 0, NULL, 0);
    }
    free(jbyte_buf_req);
    return ret;
}

