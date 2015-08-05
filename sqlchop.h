/*
 * Copyright (C) 2015 Chaitin Tech.
 *
 * Licensed under:
 *   https://github.com/chaitin/sqlchop/blob/master/LICENSE
 *
 */

#ifndef __SQLCHOP_SQLCHOP_H__
#define __SQLCHOP_SQLCHOP_H__

#define SQLCHOP_API __attribute__((visibility("default")))

#ifdef __cplusplus
extern "C" {
#endif

struct sqlchop_object_t;

enum {
  SQLCHOP_RET_SQLI = 1,
  SQLCHOP_RET_NORMAL = 0,
  SQLCHOP_ERR_SERIALIZE = -1,
  SQLCHOP_ERR_LENGTH = -2,
};

SQLCHOP_API int sqlchop_init(const char config[],
                             struct sqlchop_object_t **obj);
SQLCHOP_API float sqlchop_score_sqli(const struct sqlchop_object_t *obj,
                                     const char buf[], size_t len);
SQLCHOP_API int sqlchop_classify_request(const struct sqlchop_object_t *obj,
                                         const char request[], size_t rlen,
                                         char *payloads, size_t maxplen,
                                         size_t *plen, int detail);

SQLCHOP_API int sqlchop_release(struct sqlchop_object_t *obj);

#ifdef __cplusplus
}
#endif

#endif // __SQLCHOP_SQLCHOP_H__
