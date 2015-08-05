#!/usr/bin/env python2
#
# Copyright (C) 2015 Chaitin Tech.
#
# Licensed under: 
#   https://github.com/chaitin/sqlchop/blob/master/LICENSE
#

import os, sys
from ctypes import *
try:
    from sqlchopio_pb2 import Request, Payload, ListOfPayload
except ImportError:
    print 'ImportError: failed to import sqlchopio_pb2'
    print 'Please install protobuf-python first and then execute make to generate sqlchopio_pb2.py'
    sys.exit(10)

_cwd = os.path.dirname(os.path.realpath(__file__))

try:
    from conf import DATA_DIR
except:
    DATA_DIR = None

class SQLChop(object):
    def __init__(self, path=DATA_DIR):
        _lib = cdll.LoadLibrary(os.path.join(_cwd, 'libsqlchop.so'))
        self._lib = _lib
        self._score_sqli = _lib.sqlchop_score_sqli
        self._score_sqli.restype = c_float
        self._release = _lib.sqlchop_release
        self._release.argtypes = [c_void_p]
        self._classify_request = _lib.sqlchop_classify_request
        self._classify_request.argtypes = [c_void_p, c_char_p, c_size_t, c_char_p, c_size_t, POINTER(c_size_t), c_int]

        self._obj = c_void_p()
        path = c_char_p(path) if path else 0
        ret = _lib.sqlchop_init(path, byref(self._obj))
        assert ret == 0, 'initialize failed with error %d.' % ret

    def __del__(self):
        self._release(self._obj)

    @staticmethod
    def _serialize_request(request):
        r = Request()
        for attr in ['urlpath', 'body', 'cookie', 'boundary', 'raw']:
            if attr in request:
                setattr(r, attr, request[attr])
        s = r.SerializeToString()
        return s

    @staticmethod
    def _unserialize_payloads(s):
        list_of_payload = ListOfPayload()
        list_of_payload.ParseFromString(s)
        ret = []
        for p in list_of_payload.payloads:
            r = {}
            for attr in ['value', 'key', 'source', 'score']:
                r[attr] = getattr(p, attr)
            ret.append(r)
        return ret

    def classify_request(self, request, detail=False):
        s = SQLChop._serialize_request(request)
        if detail:
            MAXLEN = 1 << 20
            out = create_string_buffer(MAXLEN)
            outlen = c_size_t()
            ret = self._classify_request(self._obj, c_char_p(s), len(s), out, MAXLEN, byref(outlen), c_int(detail))
            return (ret, SQLChop._unserialize_payloads(out[:outlen.value]))
        else:
            ret = self._classify_request(self._obj, c_char_p(s), len(s), create_string_buffer(0), 0, byref(c_size_t()), c_int(detail))
            return (ret, [])

    def score_sqli(self, payload):
        if isinstance(payload, unicode):
            payload = payload.encode('utf-8')
        p = c_char_p(payload)
        slen = len(payload)
        ret = self._score_sqli(self._obj, p, slen)
        return ret

    def is_sqli(self, payload):
        ret = self.score_sqli(payload)
        return ret > 2.1

    def classify(self, request, detail=False):
        if isinstance(request, basestring):
            request = {'raw': request}
        result, payloads = self.classify_request(request, detail)
        return {'result': result, 'payloads': payloads}

def main():
    urlpath = ''
    body = ''
    cookie = ''
    request = {'urlpath': urlpath, 'body': body, 'cookie': cookie}
    sql = SQLChop()
    ret = sql.classify(request)
    if ret['result'] == 0:
        print 'SQLChop works!'

if __name__ == '__main__':
    main()
