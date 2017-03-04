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
    shouldDie = false;
    thread = std::thread(&Gate::threadFunc, this, OPEN);
}

void Gate::close(void) {
    if (emergency) return;
    std::lock_guard<std::mutex> lock(mtx);
    if (threadRunning) return;
    lock.~lock_guard();
    shouldDie = false;
    thread = std::thread(&Gate::threadFunc, this, CLOSED);
}

void Gate::stop(void) {
    mtx2.lock();
    shouldDie = true;
    mtx2.unlock();
    state = ALERT;
    emit gateStateInternal(state, preciseState);
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
        emit gateStateInternal(state, preciseState);
        for(; preciseState <= 100; preciseState += 10) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::lock_guard<std::mutex> lock(mtx2);
            if (shouldDie) return;
            mtx2.unlock();
        }
    } else if (target == CLOSED) {
        emit gateStateInternal(state, preciseState);
        for(; preciseState >= 0; preciseState -= 10) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::lock_guard<std::mutex> lock(mtx2);
            if (shouldDie) return;
            mtx2.unlock();
        }
    }

    state = target;

    mtx.lock();
    threadRunning = false;
    mtx.unlock();
}
