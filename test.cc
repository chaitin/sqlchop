/*
 * Copyright (C) 2015 Chaitin Tech.
 *
 * Licensed under:
 *   https://github.com/chaitin/sqlchop/blob/master/LICENSE
 *
 * Sample usage:
 *   $ LD_LIBRARY_PATH=./ ./test
 *
 */


#include <string>
#include <iostream>

#include "sqlchop.h"
#include "sqlchopio.pb.h"

#define MAXLEN 1 << 20

using namespace std;

sqlchop_object_t *pdetector;
string str_in;
char out[MAXLEN];

Request req;
ListOfPayload list_of_payload;

int main() {

  req.set_urlpath("/chaitin/"
                  "sqlchop?="
                  "c2VsZWN0JTIwc3FsY2hvcCUyMGZyb20lMjBjaGFpdGluJTIwd2hlcmUlMjBo"
                  "ZWxsbyUyMCUzRCUyMHdvcmxkJTIwJTI2JTI2JTIwJTI3aG9wZSUyNyUyMCUy"
                  "N3lvdSUyNyUyMGxpa2UlMjBpdAo=");
  req.SerializeToString(&str_in);

  size_t out_len;
  sqlchop_init(0, &pdetector);
  sqlchop_classify_request(pdetector, str_in.c_str(), str_in.length(), out,
                           MAXLEN, &out_len, 1);

  list_of_payload.ParseFromString(string(out, out_len));

  for (int pi = 0; pi < list_of_payload.payloads_size(); pi++) {
    cout << "Payload #" << pi << ":" << endl;
    const Payload& payload = list_of_payload.payloads(pi);
    cout << "Value:" << endl;
    cout << payload.value() << endl;
    if (payload.has_key()) {
      cout << "Key:" << endl;
      cout << payload.key() << endl;
    }
    if (payload.has_source()) {
      cout << "Source:" << endl;
      cout << payload.source() << endl;
    }
    if (payload.has_score()) {
      cout << "Score:" << endl;
      cout << payload.score() << endl;
    }
    cout << endl;
  }

  return 0;
}
