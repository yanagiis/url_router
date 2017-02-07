/* BSD 3-Clause License

Copyright (c) 2017, yanagiis@gmail.com
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef URL_ROUTER_H
#define URL_ROUTER_H

#include <stdbool.h>

typedef void Args;
typedef void UrlRouter;

typedef enum URL_ROUTER_ERROR {
    URL_ROUTER_E_OK = 0,
    URL_ROUTER_E_NO_MEMORY = 1,
    URL_ROUTER_E_WRONG_PARAMETER = 2,
    URL_ROUTER_E_URL_EXISTED = 3,
    URL_ROUTER_E_NOT_FOUND = 4
} URL_ROUTER_ERROR;

void url_router_args_free(Args *l);
bool url_router_args_get(Args *l, const char *key, const int klen, const char **val, int *vlen);

UrlRouter *url_router_new();
void url_router_free(UrlRouter *r);
URL_ROUTER_ERROR url_router_insert(UrlRouter *r, const char *key, void *data);
URL_ROUTER_ERROR url_router_insertl(UrlRouter *r, const char *key, int klen, void *data);
URL_ROUTER_ERROR url_router_match(UrlRouter *r, const char *key, Args *arg, void **data);
URL_ROUTER_ERROR url_router_matchl(UrlRouter *r, const char *key, int klen, Args *arg, void **data);

#endif /* URL_ROUTER_H */
