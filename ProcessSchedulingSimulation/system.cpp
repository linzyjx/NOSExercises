//
// Created by linzy on 2019/03/21.
//
#include "system.h"

void Sys::init(std::vector<inProcess> ps) {
    runtime = 0;
//初始化进程列表
    for (auto psi = ps.begin(); psi != ps.end(); psi++) {
        process i;
        i.pid = psi.base()->pid;
        i.arrTime = psi.base()->arrTime;
        i.sevTime = psi.base()->sevTime;
        i.startTime = -1;
        i.endTime = 0;
        i.runTime = 0;
        i.done = false;
        processList.push_back(i);
    }
    idleProcess.arrTime = 0;
    idleProcess.sevTime = 0;
    idleProcess.startTime = -1;
    idleProcess.endTime = 0;
    idleProcess.runTime = 0;
    idleProcess.pid = 0;
}

void Sys::runtask(Sys::process *p) {
    if (p->done) return;
    std::cout << "[" << runtime << "]run process " << p->pid << std::endl;
    if (p->startTime < 0) p->startTime = runtime;
    runtime++;
    p->runTime++;
    if (p->runTime >= p->sevTime) {
        if (p != &idleProcess)p->done = true;
        p->endTime = runtime;
    }
}

void Sys::system(int n) {
    while (n--) {
        for (auto psi = processList.begin(); psi != processList.end(); psi++) {
            if (psi.base()->arrTime == runtime) {
                pushProcess(psi.base());
            }
        }
        process *p = getNextRunProcess();
        if (!p) {
//            std::cout << "empty task" << std::endl;
            p = &idleProcess;
        }
        runtask(p);
    }
}

void Sys::printProcessList() {
    std::cout << std::internal << std::setw(5) << "PID" << std::setw(15) << "到达时间" << std::setw(15)
              << "服务时间" << std::setw(21) << "开始运行时间" << std::setw(21) << "完成运行时间" << std::setw(15) << "周转时间"
              << std::setw(21) << "带权周转时间" << std::endl;
    int sumTaskTime = 0;
    float sumWeightTaskTime = 0;
    for (auto psi = processList.begin(); psi != processList.end(); psi++) {
        std::cout << std::internal << std::setw(4) << psi.base()->pid << std::setw(8) << psi.base()->arrTime
                  << std::setw(9) << psi.base()->sevTime << std::setw(12)
                  << psi.base()->startTime << std::setw(13) << psi.base()->endTime << std::setw(11)
                  << psi.base()->taTime() << std::setw(15) << psi.base()->taTime() / (float) psi.base()->sevTime
                  << std::endl;
        sumTaskTime += psi.base()->taTime();
        sumWeightTaskTime += psi.base()->taTime() / (float) psi.base()->sevTime;
    }
    std::cout << "作业平均周转时间：" << sumTaskTime /(float) processList.size() << std::endl;
    std::cout << "作业带权平均周转时间：" << sumWeightTaskTime / processList.size() << std::endl;
}

//**************************************************
//FCFS算法
FCFS::FCFS(std::vector<inProcess> ps) {
    init(ps);
}

bool FCFS::pushProcess(process *p) {
    processQueue.push(p);
    return true;
}

FCFS::process *FCFS::getNextRunProcess() {
    if (processQueue.empty()) return nullptr;
    if (processQueue.front()->done) {
        processQueue.pop();
    }
    return processQueue.front();
}

void FCFS::initScheduling() {

}

//********************************************
//SJF算法
SJF::SJF(std::vector<inProcess> ps) {
    init(ps);
}

bool SJF::pushProcess(process *p) {
    processQueue.push_back(p);
    return true;
}

SJF::process *SJF::getNextRunProcess() {
    if (processing != nullptr && !processing->done) {
        return processing;
    }
    if (processQueue.empty()) return nullptr;
    process *minp = processQueue.begin().operator*();
    for (auto pqi = processQueue.begin(); pqi != processQueue.end(); pqi++) {
        if (pqi.operator*()->done) {
            processQueue.erase(pqi);
            if (processQueue.empty()) return nullptr;
            pqi = processQueue.begin();
            continue;
        }
        if (pqi.operator*()->sevTime < minp->sevTime) {
            minp = pqi.operator*();
        }
    }
    processing = minp;
    return minp;
}

void SJF::initScheduling() {

}

//********************************************
//HRF（最高响应比优先）算法
//R=1
HRF::HRF(std::vector<inProcess> ps) {
    init(ps);
}

bool HRF::pushProcess(process *p) {
    processQueue.push_back(p);
    return true;
}

HRF::process *HRF::getNextRunProcess() {
    if (processing != nullptr && !processing->done) {
        return processing;
    }
    if (processQueue.empty()) return nullptr;
    process *maxp = processQueue.begin().operator*();
    for (auto pqi = processQueue.begin(); pqi != processQueue.end(); pqi++) {
        if (pqi.operator*()->done) {
            processQueue.erase(pqi);
            if (processQueue.empty()) return nullptr;
            pqi = processQueue.begin();
            continue;
        }
        if (requestTime(*pqi) > requestTime(maxp)) {
            maxp = pqi.operator*();
        }
    }
    processing = maxp;
    return maxp;
}

float HRF::requestTime(Sys::process *p) {
    return ((runtime - p->arrTime) + p->sevTime) / p->sevTime;
}

void HRF::initScheduling() {

}


//**************************************************
//时间片轮转算法
//时间片长度为1
TimeSlice::TimeSlice(std::vector<inProcess> ps) {
    init(ps);
}

bool TimeSlice::pushProcess(process *p) {
    processQueue.push(p);
    return true;
}

TimeSlice::process *TimeSlice::getNextRunProcess() {
    if (processQueue.empty()) return nullptr;
    if (processQueue.front()->done) {
        processQueue.pop();
        if (processQueue.empty()) return nullptr;
    }
    process *p = processQueue.front();
    processQueue.pop();
    processQueue.push(p);
    return p;
}

void TimeSlice::initScheduling() {

}