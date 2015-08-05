#!/usr/bin/env python2
#
# Copyright (C) 2015 Chaitin Tech
#
# Licensed under:
#   https://github.com/chaitin/sqlchop/blob/master/LICENSE
#

import pprint
from sqlchop import *

pp = pprint.PrettyPrinter(indent=2)

detector = SQLChop()

pp.pprint(detector.classify({'urlpath': '/chaitin/sqlchop?=c2VsZWN0JTIwc3FsY2hvcCUyMGZyb20lMjBjaGFpdGluJTIwd2hlcmUlMjBoZWxsbyUyMCUzRCUyMHdvcmxkJTIwJTI2JTI2JTIwJTI3aG9wZSUyNyUyMCUyN3lvdSUyNyUyMGxpa2UlMjBpdAo=' }, True))
