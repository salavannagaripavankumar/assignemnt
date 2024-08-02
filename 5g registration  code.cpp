#include <iostream>
#include <string>

enum class RMState {
    RM_DEREGISTERED,
    RM_REGISTERED
};

enum class Message {
    REGISTRATION_ACCEPT,
    REGISTRATION_REJECT,
    DEREGISTRATION,
    REGISTRATION_REQUEST
};

class UE {
private:
    RMState state;

public:
    UE() : state(RMState::RM_DEREGISTERED) {}

    void sendMessageToAMF(Message msg) {
        std::cout << "UE -> AMF: ";
        switch (msg) {
            case Message::REGISTRATION_REQUEST:
                std::cout << "Sending Registration Request." << std::endl;
                break;
            default:
                std::cout << "Unknown message." << std::endl;
                break;
        }
    }

    void receiveMessageFromAMF(Message msg) {
        std::cout << "AMF -> UE: ";
        switch (msg) {
            case Message::REGISTRATION_ACCEPT:
                std::cout << "Received Registration Accept." << std::endl;
                state = RMState::RM_REGISTERED;
                break;
            case Message::REGISTRATION_REJECT:
                std::cout << "Received Registration Reject." << std::endl;
                state = RMState::RM_DEREGISTERED;
                break;
            case Message::DEREGISTRATION:
                std::cout << "Received Deregistration." << std::endl;
                state = RMState::RM_DEREGISTERED;
                break;
            default:
                std::cout << "Unknown message." << std::endl;
                break;
        }
        printState();
    }

    void printState() {
        std::string stateStr = (state == RMState::RM_REGISTERED) ? "REGISTERED" : "DEREGISTERED";
        std::cout << "UE State: " << stateStr << std::endl;
    }
};

class AMF {
private:
    RMState state;

public:
    AMF() : state(RMState::RM_DEREGISTERED) {}

    void receiveMessageFromUE(Message msg) {
        std::cout << "UE -> AMF: ";
        if (msg == Message::REGISTRATION_REQUEST) {
            std::cout << "Received Registration Request." << std::endl;
            // Decide to accept or reject based on some logic
            sendMessageToUE(Message::REGISTRATION_ACCEPT); // Example decision
        }
    }

    void sendMessageToUE(Message msg) {
        std::cout << "AMF -> UE: ";
        switch (msg) {
            case Message::REGISTRATION_ACCEPT:
                std::cout << "Sending Registration Accept." << std::endl;
                state = RMState::RM_REGISTERED;
                break;
            case Message::REGISTRATION_REJECT:
                std::cout << "Sending Registration Reject." << std::endl;
                state = RMState::RM_DEREGISTERED;
                break;
            case Message::DEREGISTRATION:
                std::cout << "Sending Deregistration." << std::endl;
                state = RMState::RM_DEREGISTERED;
                break;
            default:
                std::cout << "Unknown message." << std::endl;
                break;
        }
        printState();
    }

    void printState() {
        std::string stateStr = (state == RMState::RM_REGISTERED) ? "REGISTERED" : "DEREGISTERED";
        std::cout << "AMF State: " << stateStr << std::endl;
    }
};

int main() {
    UE ue;
    AMF amf;

    // UE sends a registration request to AMF
    ue.sendMessageToAMF(Message::REGISTRATION_REQUEST);
    amf.receiveMessageFromUE(Message::REGISTRATION_REQUEST);

    // AMF decides to accept or reject
    // This is already handled in the `receiveMessageFromUE` method of the AMF

    // Simulate a deregistration request initiated by the AMF
    amf.sendMessageToUE(Message::DEREGISTRATION);
    ue.receiveMessageFromAMF(Message::DEREGISTRATION);

    return 0;
}
