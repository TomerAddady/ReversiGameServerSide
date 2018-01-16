//
// Created by tomer on 14/01/18.
//

#ifndef SERVER_TASK_H
#define SERVER_TASK_H


class Task {

public:
    /**
     * the Constructor.
     * @param func the function that we will run.
     * @param arg the arguments to the func that descibed above.
     */
    Task(void * (*func)(void *arg), void* arg) : func(func), arg(arg) {}
    /**
     * execute the function with the args
     */
    void execute() {
        func(arg);
    }
    /**
     * destructor
     */
    virtual ~Task() {}
private:
    // a function pointer.
    void * (*func)(void *arg);
    // parameter to the function.
    void *arg;


};


#endif //SERVER_TASK_H
