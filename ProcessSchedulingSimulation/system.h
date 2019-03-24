//
// Created by linzy on 2019/03/21.
//

#ifndef NETWORKOS_MAIN_H
#define NETWORKOS_MAIN_H

#include <vector>
#include <queue>
#include <iomanip>
#include <iostream>

//输入用进程结构体
struct inProcess {
    int pid;        //进程ID
    int arrTime;    //到达时间
    int sevTime;    //服务时间
};

//系统类
//负责模拟系统调度和进程管理
class Sys {
public:
    void init(std::vector<inProcess>);  //初始化

    void system(int);   //模拟系统调度

    void printProcessList();    //打印进程列表

protected:
    struct process {
        int pid;        //进程ID
        int arrTime;    //到达时间
        int sevTime;    //服务时间
        int startTime = -1;  //开始运行时间
        int endTime;    //结束运行时间
        int taTime() { //周转时间
            return endTime - arrTime;
        }

        int runTime;    //实际运行时间
        bool done = false;   //任务完成
        int priority = 0;  //优先级
    };

    int runtime;    //CPU运行时间
    std::vector<process> processList;   //进程列表
    process idleProcess;    //系统空闲进程,PID=0

    void runtask(process *);    //执行一个单位时间的任务

    virtual bool pushProcess(process *) = 0;//推送任务给算法队列

    virtual process *getNextRunProcess() = 0;//使用调度算法获取下一个运行进程

    virtual void initScheduling() = 0;//初始化调度算法
};

//FCFS算法类
class FCFS : public Sys {
public:
    FCFS(std::vector<inProcess> ps);

protected:
    bool pushProcess(process *);

    process *getNextRunProcess();

    void initScheduling();

private:
    std::queue<process *> processQueue;
};


class SJF : public Sys {
public:
    SJF(std::vector<inProcess> ps);

protected:
    bool pushProcess(process *);

    process *getNextRunProcess();

    void initScheduling();

private:
    std::vector<process *> processQueue;
    process *processing = nullptr;
};


class HRF : public Sys {
public:
    HRF(std::vector<inProcess> ps);

protected:
    bool pushProcess(process *);

    process *getNextRunProcess();

    void initScheduling();

private:
    std::vector<process *> processQueue;

    float requestTime(process *);

    process *processing = nullptr;
};


class TimeSlice : public Sys {
public:
    TimeSlice(std::vector<inProcess> ps);

protected:
    bool pushProcess(process *);

    process *getNextRunProcess();

    void initScheduling();

private:
    std::queue<process *> processQueue;
};

#endif //NETWORKOS_MAIN_H
