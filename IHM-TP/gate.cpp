#include <QPainter>
#include <QPixmap>
#include <QString>
#include <thread>
#include <chrono>
#include "gate.h"
#include "enums.h"

Gate::Gate()
{

}

Gate::Gate(QString gi) {
    img = QPixmap(gi);
}

void Gate::emergencyStop() {
    if (emergency) return;
    stop();
    emergency = true;
    state = ALERT;
    emit gateStateInternal(state, preciseState);
}

void Gate::endEmergencyStop() {
    if (!emergency) return;
    emergency = false;
    state = STOPPED;
}

void Gate::paint(QPainter* p) {
    int y = 0 - 2 * preciseState;
    p->drawPixmap(0, y, img);
}

void Gate::open(void) {
    if (emergency) return;
    std::lock_guard<std::mutex> lock(mtx);
    mtx.lock();
    if (threadRunning) return;
    mtx.unlock();
    shouldDie = false;
    state = OPENING;
    thread = std::thread(&Gate::threadFunc, this, OPEN);
}

void Gate::close(void) {
    if (emergency) return;
    std::lock_guard<std::mutex> lock(mtx);
    mtx.lock();
    if (threadRunning) return;
    mtx.unlock();
    shouldDie = false;
    state = CLOSING;
    thread = std::thread(&Gate::threadFunc, this, CLOSED);
}

void Gate::stop(void) {
    mtx2.lock();
    shouldDie = true;
    mtx2.unlock();
    state = STOPPED;
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
        for(; preciseState <= 100; preciseState += 10) {
            emit gateStateInternal(state, preciseState);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::lock_guard<std::mutex> lock(mtx2);
            mtx2.lock();
            if (shouldDie) {
                mtx.lock();
                threadRunning = false;
                mtx.unlock();
                return;
            }
            mtx2.unlock();
        }
    } else if (target == CLOSED) {
        for(; preciseState >= 0; preciseState -= 10) {
            emit gateStateInternal(state, preciseState);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::lock_guard<std::mutex> lock(mtx2);
            if (shouldDie) {
                mtx.lock();
                threadRunning = false;
                mtx.unlock();
                return;
            }
            mtx2.unlock();
        }
    }

    state = target;

    if (target == OPEN) {
        preciseState = 100;
    } else if (target == CLOSED) {
        preciseState = 0;
    }

    emit gateStateInternal(state, preciseState);

    mtx.lock();
    threadRunning = false;
    mtx.unlock();
}
