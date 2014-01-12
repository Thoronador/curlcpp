//
//  http_post.h
//  curl_wrapper
//
//  Created by Giuseppe Persico on 11/01/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef __curl_wrapper__http_post__
#define __curl_wrapper__http_post__

#include <iostream>
#include <vector>
#include <algorithm>
#include <curl/curl.h>

using std::vector;
using std::for_each;

class curl_http_post {
public:
    template<class T> class form_pair;
    curl_http_post() : form_post(nullptr), last_ptr(nullptr) {}
    ~curl_http_post();
    template<typename T> curl_http_post &form_add(const curl_http_post::form_pair<T> &);
    template<typename T> curl_http_post &form_add(const vector<curl_http_post::form_pair<T>> &);
    struct curl_httppost *get_form_post() const noexcept { return this->form_post; }
private:
    struct curl_httppost *form_post;
    struct curl_httppost *last_ptr;
};


template<typename T> curl_http_post &curl_http_post::form_add(const curl_http_post::form_pair<T> &pair) {
    curl_formadd(&this->form_post,&this->last_ptr,pair.first(),pair.second(),CURLFORM_END);
    return *this;
}

template<typename T> curl_http_post &curl_http_post::form_add(const vector<curl_http_post::form_pair<T> > &pairs) {
    for_each(pairs.begin(),pairs.end(),[this](curl_http_post::form_pair<T> pair) { this->form_add(pair); } );
    return *this;
}

#endif /* defined(__curl_wrapper__http_post__) */
