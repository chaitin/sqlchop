package cn.chaitin.sqlchop;

import java.io.UnsupportedEncodingException;

import java.lang.Boolean;
import java.lang.String;
import java.lang.System;
import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;

import com.google.protobuf.ByteString;
import com.google.protobuf.InvalidProtocolBufferException;

import cn.chaitin.sqlchop.protobuf.Sqlchopio;


public class SQLChop {
    
    class ClassifyResult {
        int result;
        Sqlchopio.ListOfPayload payloads;

        ClassifyResult(int result, Sqlchopio.ListOfPayload payloads) {
            this.result = result;
            this.payloads = payloads;
        }

        @Override
        public String toString() {
            return "result : " + result + "\npayloads : " + payloads;
        }
    }

    long sqlchop;
    //sqlchop_object_t point, do not remove it

    static {
        System.loadLibrary("SQLChopJni");
    }

    public SQLChop() {
        init();
    }

    public void finalize() {
        release();
    }

    private native int init();
    private native void release();
    private native float score_sqli(String payload);
    private native int classify_request(byte[][] buf, boolean detail);

    private static Sqlchopio.Request buildRequest(String urlpath, String body, String cookie, String boundary, String raw) {
        Sqlchopio.Request.Builder builder = Sqlchopio.Request.newBuilder();
        if (urlpath != null) {
            builder.setUrlpath(ByteString.copyFromUtf8(urlpath));
        }
        if (body != null) {
            builder.setBody(ByteString.copyFromUtf8(body));
        }
        if (cookie != null) {
            builder.setCookie(ByteString.copyFromUtf8(cookie));
        }
        if (boundary != null) {
            builder.setBoundary(ByteString.copyFromUtf8(boundary));
        }
        if (raw != null) {
            builder.setRaw(ByteString.copyFromUtf8(raw));
        }
        return builder.build();
    }

    public float score (String payload) {
        try {
            return score_sqli(payload);
        } catch (Exception e) {
            return -1;
        }
    }

    public Boolean isSqli(String payload) {
        return score(payload) > 2.1;
    }

    public ClassifyResult classify(Sqlchopio.Request request, Boolean detail) throws InvalidProtocolBufferException {
        byte[][] buf = new byte[2][];
        buf[0] = request.toByteArray();
        buf[1] = null;
        // 0 for input, 1 for output

        int result = classify_request(buf, detail);
        Sqlchopio.ListOfPayload payloads = null;
        if (detail) { 
            payloads = Sqlchopio.ListOfPayload.parseFrom(buf[1]);
        }
        System.out.println(buf[1].length);
        //System.out.println(payloads);


        return new ClassifyResult(result, payloads);
    }

    public ClassifyResult classify(Sqlchopio.Request request) throws InvalidProtocolBufferException {
        return classify(request, false);
    }

    public ClassifyResult classify(byte[] raw, Boolean detial) throws UnsupportedEncodingException, InvalidProtocolBufferException{
        Sqlchopio.Request request = buildRequest(null, null, null, null, new String(raw, "UTF-8"));
        return classify(request, detial);
    }

    public ClassifyResult classify(byte[] raw) throws UnsupportedEncodingException, InvalidProtocolBufferException {
        return classify(raw, false);
    }

    public static void main(String[] args) throws Exception {
        SQLChop sql = new SQLChop();
        System.out.println(sql.score_sqli("' and 1=2 union select test from admin where 1 > 2"));
        Sqlchopio.Request request = buildRequest("http://www.chaitin.cn/sqlchop?test=hello", "a=1&b=2", "c=3;d=4' and 1=2 union select 1 from admin #", "test", "monster");
        ClassifyResult ret = sql.classify(request, true);
        System.out.println(ret);
    }
}
