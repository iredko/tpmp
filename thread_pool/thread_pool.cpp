/* 
 * File:   thread_pool.cpp
 * Author: iredko
 * 
 * Created on October 27, 2014, 12:13 PM
 */

#include <boost/asio/io_service.hpp>

#include "thread_pool.h"

thread_pool::thread_pool(unsigned int thread_max = 4) {
    work = new boost::asio::io_service::work(ioService);
    for (unsigned i = 0; i < thread_max; i++){
        threadpool.create_thread(
        boost::bind(&boost::asio::io_service::run, &ioService)
        );
    }
}

thread_pool::~thread_pool(){
//    ioService.stop();
    delete work;
    threadpool.join_all();
}
