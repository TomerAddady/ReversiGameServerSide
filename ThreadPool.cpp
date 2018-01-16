//
// Created by tomer on 14/01/18.
//

#include <zconf.h>
#include <iostream>
#include "ThreadPool.h"
using  namespace std;
ThreadPool::ThreadPool(int threadsNum) : stopped(false) {
    threads = new pthread_t[threadsNum];
    for (int i = 0; i < threadsNum; i++) {
        pthread_create(threads + i, NULL, execute, this);
    }
    pthread_mutex_init(&lock, NULL);
}

void *ThreadPool::execute(void *arg) {
    ThreadPool *pool = (ThreadPool *) arg;
    pool -> executeTasks();
}


void ThreadPool::addTask(Task *task) {
    tasksQueue.push(task);
}


void ThreadPool::executeTasks() {
    while (!stopped) {
        pthread_mutex_lock(&lock);
        if (!tasksQueue.empty()) {
            Task* task = tasksQueue.front();
            tasksQueue.pop();
            pthread_mutex_unlock(&lock);
            task->execute();
            delete(task);
        }
        else {
            pthread_mutex_unlock(&lock);
            cout << "im working" << endl;
            sleep(1);
        }
        cout << "im working" << endl;

    }
}

void ThreadPool::terminate() {
    pthread_mutex_destroy(&lock);
    stopped = true;
}

ThreadPool::~ThreadPool() {
    delete[] threads;
}