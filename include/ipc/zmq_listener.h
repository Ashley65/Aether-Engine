//
// Created by DevAccount on 07/10/2025.
//

#ifndef OPENWORLD_ZMQ_LISTENER_H
#define OPENWORLD_ZMQ_LISTENER_H
#pragma once
#include <QObject>
#include <zmq.hpp>
#include <QSocketNotifier>

class ZMQListener : public QObject
{
    Q_OBJECT

    public:
    explicit ZMQListener(zmq::context_t& context, QObject *parent = nullptr);

private slots:
    void onSocketReady(); // Slot to handle incoming messages from the firmware
private:
    zmq::socket_t m_socket; // ZeroMQ socket for communication
    QSocketNotifier* socketNotifier; // Notifier for socket events
};

#endif //OPENWORLD_ZMQ_LISTENER_H