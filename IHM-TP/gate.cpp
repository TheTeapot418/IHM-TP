#include <QPaintEvent>
#include <thread>
#include <chrono>
#include "gate.h"
#include "enums.h"

Gate::Gate()
{

}

void Gate::emergencyStop() {
    stop();
    emergency = true;
}

void Gate::endEmergencyStop() {
    emergency = false;
    state = STOPPED;
}

void Gate::paint(QPaintEvent *) {

}

void Gate::open(void) {
    if (emergency) return;
    std::lock_guard<std::mutex> lock(mtx);
    if (threadRunning) return;
    lock.~lock_guard();
    thread = std::thread(threadFunc, OPEN);
}

void Gate::close(void) {
    if (emergency) return;
    std::lock_guard<std::mutex> lock(mtx);
    if (threadRunning) return;
    lock.~lock_guard();
    thread = std::thread(threadFunc, CLOSED);
}

void Gate::stop(void) {
    std::terminate(thread);
    state = ALERT;
}

State Gate::getState(void) {
    return state;
}

int Gate::getPreciseState(void) {
    return preciseState;
}

void Gate::threadFunc(State target) {
    mtx.lock();
    threadRunning = true;
    mtx.unlock();

    if (target == OPEN) {
        for(; preciseState <= 100; preciseState += 10) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } else if (target == CLOSED) {
        for(; preciseState >= 0; preciseState -= 10) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    state = target;

    mtx.lock();
    threadRunning = false;
    mtx.unlock();
}
