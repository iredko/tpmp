/* 
 * File:   thread_pool.h
 * Author: iredko
 *
 * Created on October 27, 2014, 12:13 PM
 */

#ifndef THREAD_POOL_H
#define	THREAD_POOL_H
#include <thread>
#include <vector>
#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

class thread_pool {
public:
    thread_pool(unsigned int thread_max);
    template <class F> void operator,(F f){
        ioService.post(f);
    }
    virtual ~thread_pool();
private:
    boost::asio::io_service::work *work;
    boost::asio::io_service ioService;
    boost::thread_group threadpool;
};

#endif	/* THREAD_POOL_H */

