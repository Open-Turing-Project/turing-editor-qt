#ifndef SIGNALMULTIPLEXER_H
#define SIGNALMULTIPLEXER_H
//
#include <QObject>
#include <QPointer>
#include <QList>

/**
        @brief Class to multiplex signal and slot connections
        @author trolltech.com (original)
        @author André Somers <a.somers@rathenau.nl> (Qt 4 port)
        @ingroup common

        Class to multiplex signal and slot connections. Qt 3 code from:
        http://doc.trolltech.com/qq/qq08-action-multiplexer.html.
        Converted to Qt 4 by a.somers@rathenau.nl.

        The SignalMultiplexer class can help you in the situation where
        one set of signals should be used to control more than one object,
        but only one object at a time. Imagine the situation where you have
        build a multiple document interface, and you have a set of commands
        in your user interface that work on these open documents. Normally,
        you would want these commands only to apply to the currently active
        document. How do hook up the signals from your commands to these
        documents then? How do you prevent that every document reacts to the
        commands, or that you end up connecting and disconnecting each and
        every signal/slot connection time after time?

        This is where SignalMultiplexer comes in. The class works as a kind
        of proxy for signals. Instead of connecting your command's signals
        to the document objects directly, you connect them to a
        SignalMultiplexer instance. Then, you use the @ref setCurrentObject
        slot to indicate which object these signals should be connected to.
        The SignalMultiplexer instance takes care of connecting the signals
        to the new object, and disconnecting them from a previous object.

        Note that the SignalMultiplexer works in both directions, so your
        document can for also control things like the availability of an
        action through the multiplexer.

        @par From the page referenced above:
        The most interesting functions are connect() and disconnect().
        Instead of calling QObject::connect() when making a connection,
        for example when connecting an action's activated() signal to a
        document object's slot, we call the first SignalMultiplexer::connect()
        function and only specify the sender, which is the QAction, or
        QToolButton, etc.

        @par
        And instead of calling QObject::connect() to connect a document
        object signal, for example QTextEdit::copyAvailable(bool), to the
        application's "copy" action's setEnabled(bool) slot, we call the
        SignalMultiplexer's second connect() function, specifying the action
        as the receiver.

        @par
        The corresponding disconnect() functions remove the connections.

        Licence: GPL v. 2 or higher, at your disgression.

*/
class SignalMultiplexer : public QObject
{
Q_OBJECT

public:
        /**
                Constructor.
        */
        SignalMultiplexer(QObject *parent = 0);

        /**
                Use this connect function instead of QObject::connect() to connect
                an actions activation signal to the receiving, multiplexed object.

                @param sender the sending action or object
                @param signal the signal in the sender object that is connected to
                @param slot the slot in the receiving object that is set through @ref
                        setCurrentObject that the signal should be connected to.

                @see connect(const char *signal, QObject *receiver, const char *slot)
                @see disconnect(QObject *sender, const char *signal, const char *slot)
        */
        void connect(QObject *sender, const char *signal, const char *slot);

        /**
                Disconnects a signal connection from a sending object to a multiplexed
                receiving object.
                @see connect(const char *signal, QObject *receiver, const char *slot)
        */
        bool disconnect(QObject *sender, const char *signal, const char *slot);

        /**
                Use this connect function instead of QObject::connect() to connect
                a multiplexed object's (status) signal to an action object's slot.

                @param signal the signal in the multiplexed sender object that is set through
                        @ref setCurrentObject that the connection should be from
                @param receiver the receiving action or object
                @param slot the slot in the receiving object

                @see connect(QObject *sender, const char *signal, const char *slot)
                @see disconnect(const char *signal, QObject *receiver, const char *slot)
        */
        void connect(const char *signal, QObject *receiver, const char *slot);

        /**
                Disconencts a signal from a multiplexed object to a receiving (action)
                object.
                @see connect(const char *signal, QObject *receiver, const char *slot)
        */
        bool disconnect(const char *signal, QObject *receiver, const char *slot);

        /**
                @returns the object the connections are currently made with.
        */
        QObject *currentObject() const { return object; }

public slots:
        /**
                Sets the current object the signals that are managed by the
                SignalMultiplexer instance should be connected to. Any connections
                of these signals to the previous object will be disconnected.
                After the connections are hooked to the new object, the
                @ref currentObjectChanged signal will be emitted.

                @param newObject the new object that the signals should be connected to
        */
        void setCurrentObject(QObject *newObject);

signals:
        /**
                Emitted when a new object is set to receive the signals managed by
                this SignalMultiplexer instance.
        */
        void currentObjectChanged(QObject* newObject);

private:
        struct Connection
        {
                QPointer<QObject> sender;
                QPointer<QObject> receiver;
                const char *signal;
                const char *slot;
        };

        void connect(const Connection &conn);
        void disconnect(const Connection &conn);

        QPointer<QObject> object;
        QList<Connection> connections;
};


#endif
